for c in np.arange(5):
    if c < 2:
        print("Chocolate?")
        if c % 2 == 0:
            print("Yes sir! With or without nuts?")
else:
    if c % 2 == 1:
        print("Again!?")
    else:
        print("CHOCOLATE" + ("!" * (c * 2 - 3)))