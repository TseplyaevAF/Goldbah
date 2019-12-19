#include <iostream>

int main() {
	setlocale(0, "RUS");
	short int n, a, b, buf; unsigned char flag = 0, N;
	std::cin >> n;

	_asm {
		mov dx, [n]
		mov di, 2 // цикл, начиная с 2
		mov flag, 0
		jmp for_loop

		is_prime: 
		mov buf, ax // для хранения значения ax
		mov bl, 1 // bl = i
		mov N, al // записываем целую часть числа, переменная N будет счетчиком
		cmp N, 2
		je end_is_prime2
		dec N
		cmp ax, 1
		je end_is_prime

			for_prime:
			mov ax, buf 
			inc bl
			div bl // n / i
			cmp ah, 0 // если остаток от деления равен нулю
			je end_is_prime
			cmp bl, N // если дошли до конца цикла
			je end_is_prime2
			jmp for_prime

				end_is_prime:
			mov flag, 0
	ret
		end_is_prime2:
	mov flag, 1
	ret
		
	for_loop:
	mov cx, dx // часть числа n
		sub cx, di // каждую итерацию отнимаем новое значение di
		mov ax, di // ax = i
		call is_prime
		cmp flag, 0
		je for_loop2
		mov ax, cx // ax = n
		call is_prime

		for_loop2:
		inc di
		cmp flag, 1
		je end
		cmp di, dx
		jnz for_loop

			end:
		mov a, cx
		dec di
		mov b, di

	}

	if (flag == 1) {
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
		std::cout << "Гипотеза подтвердилась";
	}
	return 0;
}