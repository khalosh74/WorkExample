"""
Overview
This script provides a set of functions for capturing
and validating user input for a personal finance application.
 It facilitates adding new transactions to a database by
 collecting necessary details such as category, amount,
 description, and date from the user via the command line.
 The script makes use of an enumerated type (Category) for
 transaction categories and interacts with a database module
 to store the validated transactions.

Dependencies
categories: A module containing the Category enum,
which defines the allowed categories for transactions.

database: A module responsible for database operations,
 including inserting new transactions.
"""

from categories import Category  # Import the Category enum
import database

def get_user_input(prompt, required=True):
    """Generic function to get user input with an optional required flag."""
    while True:
        user_input = input(prompt).strip()
        if not required and user_input == "":
            return None
        elif user_input:
            return user_input
        else:
            print("This field is required.")

def get_transaction_category(prompt):
    while True:
        category_input = get_user_input(prompt).upper()
        try:
            # Attempt to match the user input to an enum member
            selected_category = Category[category_input]
            return selected_category
        except KeyError:
            print(f"Invalid category. Available categories are: {[cat.name for cat in Category]}")


def get_transaction_amount():
    """Prompt user for a transaction amount and validate it."""
    while True:
        try:
            amount = float(get_user_input("Enter transaction amount (use '-' for expenses): "))
            return amount
        except ValueError:
            print("Please enter a valid number.")

def get_transaction_date():
    """Prompt user for a transaction date and validate it."""
    from datetime import datetime
    while True:
        date_str = get_user_input("Enter transaction date (YYYY-MM-DD): ")
        try:
            date = datetime.strptime(date_str, "%Y-%m-%d").date()
            return date
        except ValueError:
            print("Please enter a date in the format YYYY-MM-DD.")

def add_transaction():
    print("Adding a new transaction.")
    category = get_transaction_category("Enter transaction category (GROCERIES, PERSONAL, UTILITIES, SALARY): ")
    amount = get_transaction_amount()
    date = get_transaction_date()
    description = get_user_input("Enter transaction description: ")
    database.insert_transaction(category, amount, description, date)

    print("Transaction added successfully.")
