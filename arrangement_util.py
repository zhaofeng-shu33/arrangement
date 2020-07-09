import random
def generate_test_case():
    f = open('test_case.txt', 'w')
    for i in range(1000):
        satisfied = True
        while satisfied:
            num_list = []
            num_sum = 0
            for i in range(18):
                new_num = random.gauss(3,1)
                if new_num < 0:
                    num = 0
                else:
                    num = int(new_num)
                num_list.append(num)
                num_sum += num
            if num_sum <= 50:
                satisfied = False
        write_str = ' '.join(num_list)
        write_str += ' ' + str(50 - num_sum) + '\n'
        f.write(write_str)
    f.close()

if __name__ == '__main__':
    generate_test_case()