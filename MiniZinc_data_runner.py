import os

def main(num):
    for i in range(4 , num + 1):
        os.system('minizinc --solver Chuffed --output-time' +  ' Sequential_Games.mzn basic_data/basicData_num_' + str(i) + '.dzn')
 
if __name__ == "__main__":
    num = input('Please number of data you want to run: ')
    num = int(num)
    main(num)
