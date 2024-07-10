"""
Overview

gui.py is a graphical user interface application for a Personal Finance Tracker
 built using Python's Tkinter library. It allows users to add, view, and sort
 financial transactions by category, amount, description, and date. The application
 features a modal popup for adding new transactions and a sortable table for transaction history.
"""

import tkinter as tk
from tkinter import ttk  # For a more modern widget set
from tkinter import messagebox
from datetime import datetime
from categories import Category  # Import the Category enum
import database

def validate_and_add_transaction(category, amount_str, description, date_str):

    # Validate Amount
    try:
        amount = float(amount_str)
    except ValueError:
        messagebox.showerror("Invalid Input", "Amount must be a number.")
        return False

    # Validate Date
    try:
        date = datetime.strptime(date_str, "%Y-%m-%d").date()
    except ValueError:
        messagebox.showerror("Invalid Input", "Date must be in YYYY-MM-DD format.")
        return False

    # If all validations pass, insert the transaction
    database.insert_transaction(category, amount, description, date)
    return True

def open_add_transaction_window():
    # Popup window for adding a transaction
    popup = tk.Toplevel()
    popup.title("Add Transaction")
    popup.geometry("300x200")  # Adjust size as needed
    popup.resizable(False, False)  # Make the window non-expandable

    # Make the popup modal
    popup.grab_set()
    popup.focus_set()

    # Prepare a list of category names for the Combobox
    category_names = [category.name for category in Category]

    # Category
    tk.Label(popup, text="Category:").grid(row=0, column=0, padx=10, pady=5, sticky="w")
    category_combobox = ttk.Combobox(popup, values=category_names, state="readonly")
    category_combobox.grid(row=0, column=1, padx=10, pady=5)
    category_combobox.current(0)

    # Amount
    tk.Label(popup, text="Amount:").grid(row=1, column=0, padx=10, pady=5, sticky="w")
    amount_entry = tk.Entry(popup)
    amount_entry.grid(row=1, column=1, padx=10, pady=5)

    # Description
    tk.Label(popup, text="Description:").grid(row=2, column=0, padx=10, pady=5, sticky="w")
    description_entry = tk.Entry(popup)
    description_entry.grid(row=2, column=1, padx=10, pady=5)

    # Date
    tk.Label(popup, text="Date (YYYY-MM-DD):").grid(row=3, column=0, padx=10, pady=5, sticky="w")
    date_entry = tk.Entry(popup)
    date_entry.grid(row=3, column=1, padx=10, pady=5)

    # Bottom panel for buttons
    bottom_panel = tk.Frame(popup)
    bottom_panel.grid(row=4, column=0, columnspan=2, pady=10)

    # Confirm button (Placeholder command)
    def on_confirm():
        selected_category_name = category_combobox.get()
        try:
            category = Category[selected_category_name]  # Correctly convert the selected name to an enum member
        except KeyError:
            messagebox.showerror("Invalid Input", "Please select a valid category.")
            return

        amount = amount_entry.get()
        description = description_entry.get()
        date = date_entry.get()

        if validate_and_add_transaction(category, amount, description, date):
            messagebox.showinfo("Success", "Transaction added successfully.")
            refresh_transactions_treeview()
            popup.destroy()

    confirm_btn = tk.Button(popup, text="Confirm", command=on_confirm)
    confirm_btn.grid(row=4, column=0, padx=10, pady=10)

    # Cancel button closes the popup
    cancel_btn = tk.Button(bottom_panel, text="Cancel", command=popup.destroy)
    cancel_btn.pack(side=tk.RIGHT, padx=10)


# Function to refresh and display transactions in the Listbox


def clear_history():
    database.clear_database()
    refresh_transactions_treeview()
    print("Clear history")

# Initialize the main application window
app = tk.Tk()
app.title("Personal Finance Tracker")

# Calculate initial size and position to be 50% of screen width and height, centered
screen_width = app.winfo_screenwidth()
screen_height = app.winfo_screenheight()
initial_width = screen_width // 2
initial_height = screen_height // 2
initial_x = screen_width // 4
initial_y = screen_height // 4

app.geometry(f"{initial_width}x{initial_height}+{initial_x}+{initial_y}")
app.minsize(initial_width, initial_height)  # Ensure the window is expandable but not smaller than initial size

# Top pane for buttons
top_pane = tk.Frame(app)
top_pane.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)

# Center the buttons in the top pane with padding
add_button = tk.Button(top_pane, text="Add Transaction", command=open_add_transaction_window)
add_button.pack(side=tk.LEFT, padx=10, expand=True)

clear_button = tk.Button(top_pane, text="Clear history", command=clear_history)
clear_button.pack(side=tk.RIGHT, padx=10, expand=True)

# Center pane for transaction history
center_pane = tk.Frame(app)
center_pane.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

# Transaction history view label
history_label = tk.Label(center_pane, text="Transaction History")
history_label.pack()

# Sort order flags for each column
sort_orders = {'category': True, 'amount': True, 'description': True, 'date': True}


def toggle_sort_order(column):
    """Toggle the sort order for a given column and refresh the table."""
    sort_orders[column] = not sort_orders[column]  # Toggle between True (ascending) and False (descending)
    sort_transactions(column)


def sort_transactions(column):
    """Sort transactions based on the column and the current sort order for that column."""
    if column == 'category':
        transactions = database.sort_by_category(sort_orders[column])
    elif column == 'amount':
        transactions = database.sort_by_amount(sort_orders[column])
    elif column == 'description':
        transactions = database.sort_by_description(sort_orders[column])
    elif column == 'date':
        transactions = database.sort_by_date(sort_orders[column])
    else:
        return  # Invalid column, just return

    # Now clear and repopulate the Treeview with sorted transactions
    for item in transaction_treeview.get_children():
        transaction_treeview.delete(item)

    for transaction in transactions:
        category = Category(transaction['category_id']).name  # Adjust if necessary based on your schema
        transaction_treeview.insert('', tk.END, values=(
        category, transaction['amount'], transaction['description'], transaction['date']))


# Transaction history view setup
columns = ('category', 'amount', 'description', 'date')
transaction_treeview = ttk.Treeview(app, columns=columns, show='headings')
transaction_treeview.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

# Define the column headings and associate the sorting function
for col in columns:
    transaction_treeview.heading(col, text=col.capitalize(), command=lambda c=col: toggle_sort_order(c))
    transaction_treeview.column(col, anchor=tk.CENTER)

# Initial population of the transaction table
sort_transactions('date')  # Default sort by date or choose your preference

# Scrollbar for the Treeview
scrollbar = ttk.Scrollbar(center_pane, orient=tk.VERTICAL, command=transaction_treeview.yview)
scrollbar.pack(side=tk.RIGHT, fill='y')
transaction_treeview.configure(yscroll=scrollbar.set)


def refresh_transactions_treeview():
    # Remove any existing rows in the Treeview
    for item in transaction_treeview.get_children():
        transaction_treeview.delete(item)

    # Fetch transactions from the database
    transactions = database.get_all_transactions()

    # Insert each transaction into the Treeview and apply alternating row colors
    for index, transaction in enumerate(transactions):
        category = Category(transaction['category_id']).name
        values = (category, transaction['amount'], transaction['description'], transaction['date'])
        if index % 2 == 0:
            transaction_treeview.insert('', tk.END, values=values, tags=('evenrow',))
        else:
            transaction_treeview.insert('', tk.END, values=values, tags=('oddrow',))


# Configure row tags for alternating colors
transaction_treeview.tag_configure('evenrow', background='#EEEEEE')  # Light grey for even rows
transaction_treeview.tag_configure('oddrow', background='#FFFFFF')  # White for odd rows

refresh_transactions_treeview()

app.mainloop()
