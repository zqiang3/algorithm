def read_data_str(filename):
    f = open(filename, 'r')
    ret = list()
    for line in f:
        num = int(line.strip())
        ret.append(num)

    f.close()
    return ret

    
