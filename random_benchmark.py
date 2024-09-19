#!/bin/python3
import subprocess as sbp
import os
import random

cur_path = os.path.dirname(os.path.realpath(__file__))
samples_dir = cur_path + '/samples/'
binary_dir = cur_path + '/release/'

os.system(f'mkdir -p {samples_dir}')

num_samples = 10
print('Generating', num_samples, 'samples for caches')

samples = []
for i in range(num_samples):
  file_name = f'{samples_dir}' + f'{i + 1:02}' + '.dat'
  samples.append(file_name)

  with open(file_name, 'w') as file:
    cache_sz = random.randint(0x400, 0x1000)
    elem_count = random.randint(0x4000, 0x10000)
    input_str = str(cache_sz) + ' ' + str(elem_count) + '\n'

    for j in range(elem_count):
      input_str += str(random.randint(0, 0x4000)) + ' '

    file.write(input_str)

  print('sample', i + 1, 'generated')

lfu_executable = 'lfu'
belady_executable = 'belady'
result_file = samples_dir + 'res.csv.out'

result_str = 'Sample,LFU hits,Belady hits,Belady/LFU ratio\n'

for sample in samples:
  cmd = binary_dir + lfu_executable + '<' + sample
  lfu_res = sbp.check_output(cmd, shell=True).decode('utf-8')

  cmd = binary_dir + belady_executable + '<' + sample
  belady_res = sbp.check_output(cmd, shell=True).decode('utf8')

  result_str += f'{os.path.basename(sample)},{int(lfu_res)},{int(belady_res)},{float(belady_res) / float(lfu_res):.2f}\n'

with open(result_file, 'w') as out:
  out.write(result_str)
