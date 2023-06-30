# Name : Kyumin Hwang
# University Directory ID: khwang77
# Nine-digits ID : 119134092
# Section number : 0205
# I pledge on my honor that I have not given or received any unauthorized
# assistance on this assignment

# This program will read four input and find the area of the rectangle.
# After that it will compare two rectangle area and if it is same return 0
# If one is bigger than other one it will retturn 1.
# If any of the length is negative it will just return -1.

#global variables
	.data
l1: 	.word 0
w1: 	.word 0
l2: 	.word 0
w2: 	.word 0
rect1: 	.word 0
rect2: 	.word 0
result: .word 0

	.text

main:	li 	$t0, 0
	sw 	$t0, result	# set result =0

	#operate system call scanf and get l1
	li 	$v0, 5
	syscall
	move 	$t0, $v0
	sw 	$t0, l1

	#operate system call scanf and get wl
	li 	$v0, 5
	syscall
	move 	$t1, $v0
	sw 	$t1, w1

	#operate system call scanf and get l2
	li 	$v0, 5
	syscall
	move 	$t2, $v0
	sw 	$t2, l2

	#operate system call scanf and get w2
	li 	$v0, 5
	syscall
	move 	$t3, $v0
	sw 	$t3, w2

	#check for l1<0
	blt 	$t0, 0, negative

	#check for w1<0
	blt 	$t1, 0, negative

	#check for l2<0
	blt 	$t2, 0, negative

	#check for w2<0
	blt 	$t3, 0, negative

	#caculate areas
	mul 	$t0, $t0,$t1	# rect1= l1 * w1
	sw 	$t0, rect1
	mul 	$t1, $t2,$t3	# rect2= l2 * w2
	sw 	$t1, rect2

	#compare areas
	blt 	$t0, $t1, smaller  	#if rect1 < rect2
	bgt 	$t0, $t1, bigger	#if rect1 > rect2
	j 	done 		# If the area is equal just move to done 

	# having negative length
negative:
	li 	$v0,-2	# result = -2
	sw 	$v0, result
	j done

	# when rect1 < rect2
smaller:
	li 	$v0, -1		# result =-1
	sw 	$v0, result
	j 	done 		#move to done

	# when rect1 > rect2
bigger:
	li 	$v0, 1		# result = 1 
	sw 	$v0, result
	j 	done  		# move to done

# print result and return 0
done:

	li 	$v0, 1 	# printf("%d", result)
	lw 	$a0, result
	syscall

	li 	$v0, 11	# printf("\n")
	li 	$a0, 10
	syscall

	#return 0
	li 	$v0, 10
	syscall
