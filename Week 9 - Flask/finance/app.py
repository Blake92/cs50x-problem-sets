import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    Symboldb = db.execute("SELECT * FROM portfolio WHERE id = ?",session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
    symbolUP = {}
    for symbol in Symboldb:
        UP = lookup(symbol["symbol"])
        symbolUP[symbol["symbol"]] = UP["price"]
    #for portSymbol in Symboldb:
     #   symbol = portSymbol["symbol"]
      #  shares = portSymbol["shares"]
       # symbolUP = lookup(symbol)
       # totalprice = symbolUP["price"]* shares
       # price = symbolUP["price"]
    return render_template("/index.html", symbol = Symboldb, price = symbolUP, cash = int(cash[0] ["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    date = datetime.now()
    if request.method == "POST":
        shares = request.form.get("shares")
        try:
            shares = int(request.form.get("shares"))
            if not shares:
                return apology("must provide share number",400)
            if shares < 0:
                return apology("Shares must be positive integer",400)
        except:
            return apology("Shares must be positive integer",400)
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol")
        symbolDICT = lookup(symbol)
        if (symbolDICT == None):
            return apology ("Invalid symbol",400)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session ["user_id"] )
        if (cash[0]["cash"] < symbolDICT["price"] * shares):
            return apology ("can't afford",400)
        db.execute("INSERT INTO transactions (id,symbol,shares,price,ttransacted) VALUES(?,?,?,?,?)",session["user_id"], symbolDICT["symbol"], shares, usd(symbolDICT["price"]),str(date) )
        priceUP = symbolDICT["price"] * shares
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", priceUP, session["user_id"])
        port = db.execute("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], symbolDICT["symbol"])
        if not port:
            db.execute("INSERT INTO portfolio (id,symbol,shares) VALUES (?,?,?)",session["user_id"],symbolDICT["symbol"], shares)
        else:
            sharesUP = int(port[0]["shares"]) + shares
            db.execute("UPDATE portfolio SET shares = ? WHERE id = ?",session["user_id"],sharesUP )
        return redirect ("/")

        #"""Buy shares of stock"""
    else:
        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        """Get stock quote."""
        symbolDICT = lookup(request.form.get("symbol"))
        if (symbolDICT == None):
            return apology ("Invalid symbol",400)
        return render_template ("/quote.html",symbol = symbolDICT)
    else:
        return render_template ("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
     if request.method == "POST":
        """Register user"""
        username = request.form.get("username")
        compare = db.execute( "SELECT username FROM users WHERE username = ?",username)
        if (not username or len(compare) != 0):
            return apology("must provide valid username", 400)
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)
        confirmation = request.form.get("confirmation")
        if (password != confirmation):
            return apology("passwords do not match", 400)
        password = generate_password_hash(password)

        db.execute("INSERT INTO users(username, hash) VALUES (?,?)", username, password)

        return redirect("/")

     else:
        return render_template("/register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
            if not shares:
                return apology ("must insert share number",400)
            if shares < 0:
                return apology ("shares cannot be negative",400)
        except:
            return apology ("incorret share number",400)
        port = db.execute("SELECT shares FROM porfolio WHERE id =? AND symbol = ?", session["user_id"],symbol )
        if not port or int(port[0]["shares"]) < shares:
            return apology ("You don't have enough shares",400)
        symbolUP = lookup(symbol)
        db.execute("INSERT INTO transactions (id,symbol,shares,price,ttransacted) VALUES(?,?,?,?,?)",session["user_id"],symbol,-shares,usd(symbolUP["price"]),str(date))
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",symbolUP["price"],session["user_id"])
        userShares = port - shares
        if userShares == 0:
            db.execute("DELETE FROM portfolio WHERE id = ? AND symbol = ?",session["user_id"],symbol)
        else:
            db.execute("UPDATE portfolio SET shares = ? WHERE id = ? AND symbol = ?",userShares,session["user_id"],symbol)
        return redirect("/")
    else:
        Symbol= db.execute("SELECT symbol FROM portfolio WHERE id = ?",session["user_id"])
        return render_template ("/sell.html",symbol = Symbol)
