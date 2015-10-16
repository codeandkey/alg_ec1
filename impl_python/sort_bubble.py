# Justin Stanley
# Bubble sort implementation - Python 3.5

import time
import sys

INPUT_FILE="input.dat"

def sort(list):
	flip_flag = 1
	while flip_flag:
		flip_flag = 0
		for i in range(0, len(list) - 1):
			if list[i] > list[i + 1]:
				tmp = list[i + 1]
				list[i + 1] = list[i]
				list[i] = tmp
				flip_flag = 1

def main():
	list = []

	with open(INPUT_FILE, "rb") as f:
		byte = f.read(4)
		while byte:
			list.append(int.from_bytes(byte, byteorder='little'))
			byte = f.read(4)

	print("Loaded file into " + str(len(list)) + " elements.")
	
	ref_time = time.clock()
	sort(list)
	total_time = time.clock() - ref_time;

	print("Time : " + '%f' % (total_time * 1000) + " milliseconds.")
	print("View results? (y/N) ")

	if sys.stdin.read(1) == 'y':
		for i in list:
			print(str(i) + " ")

if __name__ == "__main__":
	main()
