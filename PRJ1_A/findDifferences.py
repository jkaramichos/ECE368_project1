def showDifferences(expectedFile):
    import os

    rel_path = 'test_files/' + expectedFile
    abs_path = os.path.join(os.getcwd(), rel_path)

    #open up your actual output:
    with open("proj1-a_output") as tFile:
        actual = tFile.read().splitlines()

    #open up what you expected it to be:
    with open(abs_path) as xFile:
        expected = xFile.read().splitlines()

    #find the differences:
    for index, a in enumerate(actual):
        (aStat, _, aValue)= a.split()

        if index == 0:
            if aValue == expected[index]:
                print("wait_time_0 matches!")
            else:
                print("wait_time_0 did not match.")
                print("\tExpected value: " + expected[index])
                print("\tActual value  : " + aValue)
                print("\tDifference    : " + str(abs(float(expected[index]) - float(aValue))))
                print("\tPercent Error : " + str(abs(float(expected[index]) - float(aValue)) / float(expected[index]) * 100))

                
        elif index == 1:
            if aValue == expected[index]:
                print("wait_time_1 matches!")
            else:
                print("wait_time_1 did not match.")
                print("\tExpected value: " + expected[index])
                print("Actual value  : " + aValue)
                print("\tDifference    : " + str(abs(float(expected[index]) - float(aValue))))
                print("\tPercent Error : " + str(abs(float(expected[index]) - float(aValue)) / float(expected[index]) * 100))


        elif index == 2:
            if aValue == expected[index]:
                print("average_queue_length matches!")
            else:
                print("average_queue_length did not match.")
                print("\tExpected value: " + expected[index])
                print("\tActual value  : " + aValue)
                print("\tDifference    : " + str(abs(float(expected[index]) - float(aValue))))
                print("\tPercent Error : " + str(abs(float(expected[index]) - float(aValue)) / float(expected[index]) * 100))


        else:
            if aValue == expected[index]:
                print("CPU_busy_time matches!")
            else:
                print("CPU_busy_time did not match.")
                print("\tExpected value: " + expected[index])
                print("\tActual value  : " + aValue)
                print("\tDifference    : " + str(abs(float(expected[index]) - float(aValue))))
                print("\tPercent Error : " + str(abs(float(expected[index]) - float(aValue)) / float(expected[index]) * 100))

# if __name__ == "__main__":
#     print(showDifferences("expected3.txt"))
