import os
import sys

# Define the boilerplate content for .cpp files
cpp_boilerplate = """#include "{relative_header_path}"

namespace ly
{{


	/// Public Functions
	/// -----------------

	/// Void


	/// Override


	/// Setters


	/// Getters


	/// Private Functions
	/// -----------------


}}
"""

# Define the boilerplate content for .h files
header_boilerplate = """#pragma once

namespace ly
{{
	class {class_name}
	{{
	public:
		{class_name}();

	private:

	}};
}}
"""

# Function to calculate the relative path for the header file
def get_relative_path(file_path, root_path):
	return os.path.relpath(file_path, root_path).replace("\\", "/")

# Function to add boilerplate to a new .cpp file
def add_cpp_boilerplate(file_path, include_root):
	print(f"Checking .cpp file: {file_path}")
	file_name = os.path.basename(file_path)
	header_file = file_name.replace(".cpp", ".h")

	# Search for the header file in the include directory
	header_path = None
	for root, _, files in os.walk(include_root):
		if header_file in files:
			header_path = os.path.join(root, header_file)
			break

	if not header_path:
		print(f"Warning: Header file '{header_file}' not found. Skipping.")
		return

	# Skip if the file already contains content
	if os.path.getsize(file_path) > 0:
		print(f"{file_path} already contains content. Skipping.")
		return

	# Write the boilerplate to the .cpp file
	relative_header_path = get_relative_path(header_path, include_root)
	print(f"Adding boilerplate to .cpp file: {file_path}")
	with open(file_path, 'w') as cpp_file:
		cpp_file.write(cpp_boilerplate.format(relative_header_path=relative_header_path))
	print(f"Boilerplate added to {file_path}")

# Function to add boilerplate to a new .h file
def add_header_boilerplate(file_path):
	print(f"Checking .h file: {file_path}")
	file_name = os.path.basename(file_path)
	class_name = file_name.replace(".h", "")

	# Skip if the file already contains content
	if os.path.getsize(file_path) > 0:
		print(f"{file_path} already contains content. Skipping.")
		return

	# Write the boilerplate to the .h file
	print(f"Adding boilerplate to .h file: {file_path}")
	with open(file_path, 'w') as header_file:
		header_file.write(header_boilerplate.format(class_name=class_name))
	print(f"Boilerplate added to {file_path}")

# Directories for engine and game
engine_directories = {
	"cpp_root": r"C:\Users\narom\Documents\AllProjects\LearnCppGameEngine\LightYears\LightYearsEngine\src",
	"include_root": r"C:\Users\narom\Documents\AllProjects\LearnCppGameEngine\LightYears\LightYearsEngine\include"
}

game_directories = {
	"cpp_root": r"C:\Users\narom\Documents\AllProjects\LearnCppGameEngine\LightYears\LightYearsGame\src",
	"include_root": r"C:\Users\narom\Documents\AllProjects\LearnCppGameEngine\LightYears\LightYearsGame\include"
}

# Process both engine and game directories
def process_directories(directories):
	print(f"Processing directories: {directories}")
	# Process .cpp files
	for root, _, files in os.walk(directories["cpp_root"]):
		for file_name in files:
			if file_name.endswith(".cpp"):
				file_path = os.path.join(root, file_name)
				add_cpp_boilerplate(file_path, directories["include_root"])

	# Process .h files
	for root, _, files in os.walk(directories["include_root"]):
		for file_name in files:
			if file_name.endswith(".h"):
				file_path = os.path.join(root, file_name)
				add_header_boilerplate(file_path)

# Run the script for both the engine and game directories
try:
	print("Starting boilerplate generation...")
	process_directories(engine_directories)
	process_directories(game_directories)
	print("Boilerplate generation completed successfully.")

except Exception as e:
	print(f"Error: {e}")
	sys.exit(1)  # Exit with an error code
