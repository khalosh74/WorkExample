"""
Overview
This module, named as a placeholder database.py, provides
 essential database operations for a Personal Finance Tracker
 application. It interfaces with an SQLite database to perform
 CRUD (Create, Read, Update, Delete) operations related to
 financial transactions. Each function is designed to interact
 with the Transactions table in the database, facilitating actions
 such as inserting new transactions, retrieving transaction data,
 and clearing transaction history.

Dependencies
sqlite3: A built-in Python library for interacting with SQLite databases.

categories: A module containing the Category enum, which defines the transaction categories.
"""

import sqlite3
from categories import Category  # Import the Category enum

DATABASE_NAME = "finance_tracker.db"


def get_db_connection():
    conn = sqlite3.connect(DATABASE_NAME)
    conn.row_factory = sqlite3.Row  # This enables column access by name
    return conn


def insert_transaction(category, amount, description, date):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("INSERT INTO Transactions (category_id, amount, description, date) VALUES (?, ?, ?, ?)",
                (category.value, amount, description, date))
    conn.commit()
    conn.close()


def get_all_transactions():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT * FROM Transactions")
    transactions = cur.fetchall()
    conn.close()
    return transactions


def get_total_expenses_by_category(category):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT SUM(amount) AS total_expenses FROM Transactions WHERE category_id = ?", (category.value,))
    total = cur.fetchone()[0]
    conn.close()
    return total


def print_transactions(transactions):
    print("Transactions:")
    for transaction in transactions:
        print(dict(transaction))


def print_user_friendly_transactions(transactions):
    for transaction in transactions:
        category = Category(transaction['category_id'])
        print("{ " + category.name, transaction['amount'], transaction['description'], transaction['date'] + " }")


def clear_database():
    conn = sqlite3.connect(DATABASE_NAME)
    cur = conn.cursor()

    # WARNING: This will remove all data from the specified tables!
    cur.execute("DELETE FROM Transactions")
    cur.execute("DELETE FROM Categories")

    conn.commit()
    conn.close()
    print("Database has been cleared.")


def sort_by_category(ascending=True):
    conn = get_db_connection()
    cur = conn.cursor()
    order = 'ASC' if ascending else 'DESC'
    cur.execute(f"SELECT * FROM Transactions ORDER BY category_id {order}")
    transactions = cur.fetchall()
    conn.close()
    return transactions


def sort_by_amount(ascending=True):
    conn = get_db_connection()
    cur = conn.cursor()
    order = 'ASC' if ascending else 'DESC'
    cur.execute(f"SELECT * FROM Transactions ORDER BY amount {order}")
    transactions = cur.fetchall()
    conn.close()
    return transactions


def sort_by_description(ascending=True):
    conn = get_db_connection()
    cur = conn.cursor()
    order = 'ASC' if ascending else 'DESC'
    cur.execute(f"SELECT * FROM Transactions ORDER BY description {order}")
    transactions = cur.fetchall()
    conn.close()
    return transactions


def sort_by_date(ascending=True):
    conn = get_db_connection()
    cur = conn.cursor()
    order = 'ASC' if ascending else 'DESC'
    cur.execute(f"SELECT * FROM Transactions ORDER BY date {order}")
    transactions = cur.fetchall()
    conn.close()
    return transactions
