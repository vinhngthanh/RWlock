import subprocess

num_tests = 6
iterations_per_test = 10

with open('output1.txt', 'w') as output_file:
    for i in range(1, num_tests + 1):
        for iteration in range(1, iterations_per_test + 1):
            output_file.write(f'Running test1 on test {i} iteration {iteration}:\n')

            command = f'cat ./tests/test{i}.txt | ./test1'
            try:
                result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
                output_file.write(result.stdout)
            except subprocess.CalledProcessError as e:
                output_file.write('Failed to execute command: ' + str(e) + '\n')

            if iteration == iterations_per_test:
                output_file.write('\n')

with open('output2.txt', 'w') as output_file:
    for i in range(1, num_tests + 1):
        for iteration in range(1, iterations_per_test + 1):
            output_file.write(f'Running test2 on test {i} iteration {iteration}:\n')

            command = f'cat ./tests/test{i}.txt | ./test2'
            try:
                result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
                output_file.write(result.stdout)
            except subprocess.CalledProcessError as e:
                output_file.write('Failed to execute command: ' + str(e) + '\n')

            if iteration == iterations_per_test:
                output_file.write('\n')

with open('output3.txt', 'w') as output_file:
    for i in range(1, num_tests + 1):
        for iteration in range(1, iterations_per_test + 1):
            output_file.write(f'Running test3 on test {i} iteration {iteration}:\n')

            command = f'cat ./tests/test{i}.txt | ./test3'
            try:
                result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
                output_file.write(result.stdout)
            except subprocess.CalledProcessError as e:
                output_file.write('Failed to execute command: ' + str(e) + '\n')

            if iteration == iterations_per_test:
                output_file.write('\n')

with open('output4.txt', 'w') as output_file:
    for i in range(1, num_tests + 1):
        for iteration in range(1, iterations_per_test + 1):
            output_file.write(f'Running test4 on test {i} iteration {iteration}:\n')

            command = f'cat ./tests/test{i}.txt | ./test4'
            try:
                result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
                output_file.write(result.stdout)
            except subprocess.CalledProcessError as e:
                output_file.write('Failed to execute command: ' + str(e) + '\n')

            if iteration == iterations_per_test:
                output_file.write('\n')