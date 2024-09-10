import random
import os

os.system('mkdir -p tests')

num_tests = 10
print('Generating ', num_tests, 'tests for caches')

for i in range(num_tests):
  file_name = 'tests/test_' + f'{i + 1:02}' + '.dat'

  with open(file_name, 'w') as file:
    cache_sz = random.randint(0x400, 0x1000)
    elem_count = random.randint(0x4000, 0x10000)
    input_str = str(cache_sz) + ' ' + str(elem_count) + '\n'

    for j in range(elem_count):
      input_str += str(random.randint(0, 0x4000)) + ' '

    file.write(input_str)

  print('test ', i + 1, 'generated')
