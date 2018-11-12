# coding: utf-8
import random


class List(object):
    head = None
    tail = None
    length = 0

    def append(self, data):
        node = Node(data)
        self.length += 1
        if self.tail is None:
            self.head = node
            self.tail = node
            return

        self.tail.next = node
        self.tail = node

    def empty(self):
        return self.length == 0

    def random_pop(self):
        """随机弹出一个数据"""
        if self.empty():
            raise ValueError('no element')

        i = random.randint(1, self.length)
        count = 1

        p = cur = self.head
        while count < i:
            p = cur
            cur = cur.next
            count += 1

        if cur == self.head:
            self.head = cur.next
        else:
            p.next = cur.next

        self.length -= 1
        return cur.data
        
    def top(self, n):
        ret = []
        count = 0
        p = self.head
        while p and count < n:
            ret.append(p.data)
            p = p.next
            count += 1

        return str(ret)

    def __str__(self):
        ret = []
        p = self.head
        while p:
            ret.append(p.data)
            p = p.next

        return str(ret)


class Node(object):
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

