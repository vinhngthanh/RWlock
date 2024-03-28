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
        lock and release the lock in this case. During testing, I realized that the variables can somehow be affected even when I use atomic so I
        has to created another mutex called rmtx to lock the readLock and readUnlock function.
    rpwl.cpp:
        In this read write lock implementation that prioritizes reading, everything is the same as the rwl with an addition of an atomic integer
        called readerRequest. When a reading thread calls readLock, the readerRequest will be incremented by 1 to signal that there are readers 
        waiting. In the writeLock function, there is a while loop that check readerRequest > 0. If there are readers waiting, it will not compete
        for the lock. Once the reader aquired the lock, the readerRequest will be decremented to signal that it has left the queue.
     rwpl.cpp:
        In this read write lock implementation that prioritizes writing, everything is almost the same as rpwl.cpp but instead of keeping
        reader requests, we keep track of writer requests.
III, Observation:
    My summary shows that the version using myMutex instead of the rwl is slower in test case 1 but not by a lot. For other test cases, it is 
    faster. I did think about it a lot because the version using myMutex only allow one thread at a time so it should be slower. But in this case,
    I think my rwl is too heavily implemented that it is somehow slower.
IV, How to run:
    1, test{i}.cpp (i is the program you want to run):
        Locate to the a2 folder.
        Example compile and run of test1.cpp file with test1.txt as input.
        Compile: g++ test1.cpp -o test1
        Run: 
            Linux: cat ./tests/test1.txt | ./test1
        Output location: Terminal

    2, runner.py:
        Run: python runner.py
        Output location: output{1-4}.txt

    3, summary.py:
        Run: python summary.py
        Output location: summary.txt
