import random

def main(num):
    num = int(num)
    file = open("solverData_num_" + str(num) + ".txt" , 'w')

    file.write("% number of games is " + str(num))
    file.write("\n")
    file.write("num = " + str(num) + ";")
    file.write('\n')
    file.write("cap = " + str(5) + ";")
    file.write('\n')
    file.write("refill = " + str(2) + ";")
    file.write('\n')

    fun = []
    for i in range(num):
        fun.append(random.randint(-20,20))
    print(fun)
    
    file.write("fun = " + str(fun) + ";")
    file.write('\n')
    

if __name__ == "__main__":
    num = input("Input the number of games: ")
    main(num)
