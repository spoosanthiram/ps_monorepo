import re
import os
import sys

def camel_to_snake(directory):
    """Convert all CamelCase C++/Text files in the given directory to snake_case.
    """
    for entry in os.listdir(directory):
        entry_path = os.path.join(directory, entry)

        if os.path.isdir(entry_path):
            camel_to_snake(entry_path)

        if os.path.isfile(entry_path) and (entry.endswith(".cpp") or entry.endswith(".h") or entry.endswith(".txt")):
            new_filename = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', entry)
            new_filename = re.sub('([a-z0-9])([A-Z])', r'\1_\2', new_filename).lower()
            new_filepath = os.path.join(directory, new_filename)

            print(f"Renaming {entry_path} to {new_filepath}")
            os.system(f"git mv {entry_path} {new_filepath}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python camel_to_snake.py <directory>")
        sys.exit(1)
    if not os.path.isdir(sys.argv[1]):
        print(f"Error: {sys.argv[1]} is not a valid directory.")
        sys.exit(1)
    camel_to_snake(sys.argv[1])
