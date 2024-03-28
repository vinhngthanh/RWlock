CSC 458 - Assignment 2
Professor: Andrew Read-McFarland

Name: Vinh Nguyen (vnguy23)

I, Explanation of the file system:
    1, myMutex.cpp:
    The myMutex.cpp file contains the code for a basic mutex.

    2, test1.cpp and rwl.cpp:
    The rwl.cpp file contains the code for a basic read write lock. The test1.cpp file uses the rwl.cpp file.

    3, test2.cpp and rpwl.cpp:
    The rpwl.cpp file contains the code for a read write lock that prioritizes reading. The test2.cpp file uses the rpwl.cpp file.

    4, test3.cpp and rwpl.cpp:
    The rwpl.cpp file contains the code for a read write lock that prioritizes writing. The test3.cpp file uses the rwpl.cpp file.

    5, test4.cpp:
    The test4.cpp file contains the modified code to use myMutex.cpp directly in its code instead of a read write lock.

    6, runner.py:
    This file runs test1.cpp, test2.cpp, test3.cpp, test4.cpp on each test case 10 times and print the result to output1.txt, output2.txt, 
    output3.txt, output4.txt respectively.

    7, summary.py:
    This file reads from all the output file and summarize all the average runtime of each implementation into summary.txt file.

II, Explanation of code:
    myMutex.cpp:
        This lock only has two functions and one atomic variable. The atomic variable called locked is a boolean which is true when the lock is
        locked and false otherwise. The lock function has a while loop which will try to replace locked with true. If locked is already true, it
        will spin until locked is false. The unlock function simply sets locked to false.
    rwl.cpp:
        In this read write lock implementation, I use an atomic int called readers to keep track of number of readers. When a reader want to get
        a lock, if readers = 0 meaning the lock is there to take, it will try to aquire the lock. But if readers > 0, meaning a reader already had
        the lock, it can continue to take the lock too because many readers can take the lock at the same time. For the readUnlock function, since
        we have a lot of readers having the lock at the same time, calling unlock early can lead to wrong answer so we decrement the reader by 1
        each time the function is called. Only when reader is 0 we will release the lock for contest. writeLock and writeUnlock just try to take the
        lock and release the lock in this case.
III, How to run:
    1, knapsack_v3.c:
        Locate to the knapsack folder.
        Compile: gcc knapsack_v3.c -o knapsack_v3 -pthread
        Run: 
            Linux: cat ../a1/inputs/(test number).txt | ./knapsack_v3 (number of threads)
            Window - powershell: Get-Content '..\\a1\\inputs\\(test number).txt' | .\\knapsack_v3.exe (number of threads)
        Output location: Terminal

    2, 258_run.c:
        Locate to the output folder.
        Compile: gcc 258_run.c -o 258_run
        Run: ./258_run
        Output location: 258_output.txt

    3, 458_run.c:
        Locate to the output folder.
        Compile: gcc 458_run.c -o 458_run
        Run: ./458_run
        Output location: 458_output.txt

    4, original_run.c:
        Locate to the output folder.
        Compile: gcc original_run.c -o original_run
        Run: ./original_run
        Output location: original_output.txt

    5, 258_report.py:
        Locate to the report folder.
        Run: python ./258_report.py
        Output location: averages.txt

    6, 458_report.py:
        Locate to the report folder.
        Run: python ./458_report.py
        Output location: 458_report.txt
    
    7, graphs.ipynb:
        Open the graphs.ipynb file and run.