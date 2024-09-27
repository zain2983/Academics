import re


with open('input.txt', 'r') as file:
    data = file.read()


filtered_data = re.sub(r'[a-zA-Z0-9]', '', data)


with open('output.txt', 'w') as file:
    file.write(filtered_data)

print("Output file created : output.txt.")

