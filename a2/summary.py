filenames = ['output1.txt', 'output2.txt', 'output3.txt', 'output4.txt']

def process(content, filename):
    split = content.split("\n\n")[:-1]
    ans = ""
    for s in split:
        avg, testNum = average(s)
        ans += "Average time running test" + filename[6] + ".cpp 10 times on test case " + testNum + ":\n"
        ans += str(avg) + "\n"
    return ans

def average(str):
    split = str.split("\n")
    sum = 0
    testNum = ""
    for s in split:
        if s[0] == 'D':
            sp = s.split()
            sum += float(sp[1])
        else:
            sp = s.split()
            testNum = sp[4]
    return round(sum / 10, 2), testNum

with open('summary.txt', 'w') as summary_file:
    for filename in filenames:
        try:
            with open(filename, 'r') as read_file:
                content = read_file.read()
                summary_file.write(process(content, filename))
                summary_file.write('\n')
        except FileNotFoundError:
            print(f"Warning: '{filename}' not found. Skipping.")

