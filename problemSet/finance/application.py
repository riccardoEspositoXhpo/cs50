import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# import time related functions for timestamps
from datetime import datetime, timezone

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    owns = own_shares()
    total = 0
    # join current amount of shares with price information to display
    for symbol, shares in owns.items():
        result = lookup(symbol)
        name, price = result["name"], result["price"]
        stock_value = shares * price
        total += stock_value
        owns[symbol] = (name, shares, usd(price), usd(stock_value))
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']
    total += cash

    return render_template("index.html", owns=owns, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":

        return render_template("buy.html")

    result = lookup(request.form.get("symbol"))

    # capture strings or other invalid share values
    try:

        quantity = float(request.form.get("shares"))

    except ValueError:

        return apology("Invalid Number of Shares", 400)

    # catch the symbol being invalid
    if not result:

        return apology("Invalid Ticker", 400)

    # catch non-integer values
    if (quantity < 1) or (quantity.is_integer() == False):
        return apology("Shares must be an integer greater or equal to 1", 400)

    name = result["name"]
    price = result["price"]
    symbol = result["symbol"]
    shares = int(request.form.get("shares"))
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

    # check if user can afford the purchase
    remain = cash - price * shares

    if remain < 0:
        return apology("Insufficient Cash. Failed Purchase.")

    # deduct order cost from user's remaining balance (i.e. cash)
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, user_id)

    db.execute("INSERT INTO orders (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
               user_id, symbol, shares, price, time_now())

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol, shares, price, timestamp FROM orders WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add money to portfolio"""

    if request.method == "GET":

        return render_template("add.html")

    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    cash = int(cash)
    newCash = request.form.get("newCash")
    newCash = int(newCash)
    finalCash = cash + newCash

    db.execute("UPDATE users SET cash = ? WHERE id = ?", finalCash, user_id)

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":

        return render_template("quote.html")

    symbol = request.form.get("symbol")
    result = lookup(symbol)

    if not result:

        return apology("Invalid Ticker", 400)

    return render_template("quoted.html", name=result["name"], price=usd(result["price"]), symbol=result["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        users = db.execute("SELECT * from users where username = ?", request.form.get("username"))
        userExists = False

        if len(users) >= 1:

            if request.form.get('username') == users[0]["username"]:

                userExists = True

        # ensure username submitted
        if not request.form.get('username'):

            return apology("Must provide username.", 400)

        elif userExists:

            return apology("A user with this username already exists", 400)

        elif not request.form.get('password') or not request.form.get('confirmation'):

            return apology("Either password or confirmation are blank.", 400)

        elif (request.form.get('password') != request.form.get('confirmation')):

            return apology("Passwords do not match.", 400)

        else:

            hashedPassword = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT into users (username, hash) VALUES (?,?)", request.form.get("username"), hashedPassword)

            # Redirect user to home page
            return redirect("/login")

    else:

        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    owns = own_shares()
    if request.method == "GET":
        return render_template("sell.html", owns=owns.keys())

    symbol = request.form.get("symbol")

    try:
        shares = float(request.form.get("shares"))

    except ValueError:
        return apology("Invalid Number of Shares", 400)

    if not symbol:

        return apology("Invalid Ticker", 400)

    if (shares < 1) or (shares.is_integer() == False):

        return apology("Shares must be an integer greater or equal to 1", 400)

    # check whether there are sufficient shares to sell
    if owns[symbol] < shares:

        return apology("Cannot sell more than you own.", 400)
    # Execute sell transaction: look up sell price, and add fund to cash,
    result = lookup(symbol)
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    price = result["price"]
    remain = cash + price * shares
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remain, user_id)
    # Log the transaction into orders
    db.execute("INSERT INTO orders (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
               user_id, symbol, -shares, price, time_now())

    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


def time_now():
    """HELPER: get current UTC date and time"""
    now_utc = datetime.now(timezone.utc)
    return str(now_utc.date()) + now_utc.time().strftime("%H:%M:%S")


def own_shares():
    """Helper function: Which stocks the user owns, and numbers of shares owned. Return: dictionary {symbol: qty}"""
    user_id = session["user_id"]
    owns = {}
    result = db.execute("SELECT symbol, shares FROM orders WHERE user_id = ?", user_id)
    for item in result:
        symbol, shares = item["symbol"], item["shares"]
        owns[symbol] = owns.setdefault(symbol, 0) + shares

    # filter zero-share stocks
    owns = {k: v for k, v in owns.items() if v != 0}
    return owns