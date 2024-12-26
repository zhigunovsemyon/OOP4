/*
 Разработать шаблон структуры данных в памяти. Тип хранимого элемента - параметр
 шаблона. Шаблон содержит объект. Реализовать:
	+операции включения/удаления по заданному логическому номеру,
	загрузки хранимых элементов в структуру данных из stdin.
 Проверить работу шаблона на разработанном классе, используя его как
 параметр шаблона. Структура данных: односвязный список, элемент списка хранит
 непосредственно объект.
 */
#include "list.h"
#include <iostream>

int main()
{
	[[maybe_unused]] int nums[]{1, 4, 8, 8};
	try {
		List<int> l{};
		for (int i = 0; i < 4; ++i) {
			// l.push(nums[i]);
		}
		// while (l.size()) {
		// 	std::cout << l.pop() << ' ';
		// }
		// l.print(std::cout);
		std::cout << l << '\n';
		return 0;
	} catch (ListErrors le) {
		switch (le) {
		case LISTERR_NULLPTR_INSERTION:
			std::cerr << "Некорректный массив!\n";
			return EXIT_FAILURE;
		case LISTERR_EMPTY_EXTRACTION:
			std::cerr << "Извлечение из пустого массива!\n";
			return EXIT_FAILURE;
		case LISTERR_NO_SUCH_ELEMENT:
			std::cerr << "Неправильно указан индекс!\n";
			return EXIT_FAILURE;
		}
	}
}
