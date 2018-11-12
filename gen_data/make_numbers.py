# coding: utf-8
import random
import sys
import struct
from PyLinkList import List
import pdb

MAX_INT = 10000000
MAX = 10000000


def make_unique_numbers():
    """每个数字各不相同"""
    arr = range(MAX_INT)


    for i in xrange(MAX_INT):
        m = random.randint(0, MAX_INT - 1)
        n = random.randint(0, MAX_INT - 1)
        arr[m], arr[n] = arr[n], arr[m]

    return arr[:MAX]


def write_data_to_file_str(arr, filename):
    f = open(filename, 'w')
    for num in arr:
        f.write(str(num))
        f.write('\n')

    f.close()


def gen_numbers_b(filename):
    f = open(filename, 'wb')

    for i in xrange(MAX):
        num = random.randint(0, MAX_INT - 1)
        b_num = struct.pack('i', num)
        f.write(b_num)

    f.close()


def gen_numbers_str(filename):
    """generate MAX numbers, range: 0 <= n < MAX_INT"""
    f = open(filename, 'w')
    for i in xrange(MAX):
        num = random.randint(0, MAX_INT - 1)
        f.write(str(num))
        f.write('\n')

    f.close()


def read_numbers(filename):
    f = open(filename, 'rb')
    b_num = f.read(4)
    ret = struct.unpack('i', b_num)
    num = ret[0]
    print 'read num', num
    f.close()


filename = 'numbers.txt'
arr = make_unique_numbers()
write_data_to_file_str(arr, filename)

