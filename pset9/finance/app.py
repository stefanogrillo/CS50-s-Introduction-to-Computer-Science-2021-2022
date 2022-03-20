import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    if request.method == "GET":
        # We just need the GET method, which is set as default

        user_id = session["user_id"]

        # Create values from DB into a Table with fields of Symbol, Name, Shares, Time and add a line for Tot User Cash
        stocks = db.execute("SELECT symbol, name, SUM(shares) as totShares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        total = cash

        for stock in stocks:
            total += stock["price"] * stock["totShares"]

        return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)
    else:
        symbol = request.form.get("symbol")
