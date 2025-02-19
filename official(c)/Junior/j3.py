import re

def transform_code(code):
    uppercase_letters = re.findall(r'[A-Z]', code)
    uppercase_part = ''.join(uppercase_letters)

    integers = re.findall(r'-?\d+', code)
    sum_integers = sum(map(int, integers))
    
    new_code = uppercase_part + str(sum_integers)
    return new_code

n = int(input())
for _ in range(n):
    original_code = input().strip()
    new_code = transform_code(original_code)
    print(new_code)