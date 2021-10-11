import cs50

answer = cs50.get_string("Do you agree?  ")

if answer.lower() in ["y", "yes"]:
    print("Agreed.")
elif answer.lower() in ["n", "no"]:
    print("Not Agreed.")

