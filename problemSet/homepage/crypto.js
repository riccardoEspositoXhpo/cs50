// load DOM before running script
document.addEventListener('DOMContentLoaded', function() {

    const cryptoMap = {
        "BTC": "I guess I have to hold some Bitcoin. Initially I didn't want to invest, thinking that I've missed the wave, but I've currently bought a small bit. Truth is, if crypto investing becomes mainstream this is probably going to be the first coin people buy.",
        "ETH": "This is the coin I'm most bullish on. The ecosystem and amount of players in it is exciting. Some scalability issues need to be solved for the project to be successful.",
        "SOL": "Exciting project - I bought some of this too. I believe it can coexist with Ethereum and cater to different use cases.",
        "SHIB": "DOGE 2.0, with something like a quadrillion coins in circulation. Definitely not a serious projects, but hey I just dropped a couple of bucks for fun.",
        "LINK": "I have tried to purchase some of it, mainly because I'm intrigued by the interoperability between chains.",
        "DOT": "I honestly don't remember why I got this, potentially because it is a popular one!",
        "USDT": "You need some stablecoins in your portfolio when you trade in and out. I'm still not convinced USDT is legit though so I own a minimal amount.",
        "BUSD": "Most of my stablecoin is held here. So you can guess which exchange I trade in.",
        "DAI": "I'm intriguied by this stablecoin, so I kind of treat is as an investment in itself. The value won't go up by construct, but the Savings rate is fantastic.",
        "ADA": "I was extremely excited when I heard about this one. As of end-2021 it's been lagging behind the others (ETH/SOL) unfortunately, not sure what the future holds.",
        "XLM": "Extremely fast, efficient payments network. I have actually used it myself. Not sure about mainstream adoption but it definitely is a useful coin.",
        "MATIC": "AKA The Internet of Blockchains. I do believe this is a valid and useful project.",
        "BNB": "I used to hold a decent amount of this. More traders equals higher value... but of course I sold it just before it's peak. classic n00b trader.",
        "DOGE": "When you coin's value is extremely correlated with Elon Musks's twitter feed, you know you have a winner. Jokes aside, the profit potential is probably over, but doesn't hurt to hold just a little bit...",
        "NOVALUE": "No Value Provided"
    };

    const keys = Object.keys(cryptoMap);
    var output;
    let check = document.querySelector('.check');
    check.addEventListener('click', function() {
        input = document.querySelector('#cryptoId').value || "NOVALUE";

        for (key in keys) {
            if (input === keys[key])
            {
                output = cryptoMap[keys[key]];
            }
        }
        document.querySelector('#feedbackCrypto').innerHTML = output || "The selected coin is either not part of my investments or does not exist.";
    });

});