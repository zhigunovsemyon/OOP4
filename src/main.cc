/*
 Разработать шаблон структуры данных в памяти. Тип хранимого элемента - параметр
 шаблона. Шаблон содержит объект. Реализовать операции включения/удаления по
 заданному логическому номеру, поиск минимального/максимального, включение с
 сохранением порядка, сортировки выбором или вставками, загрузки хранимых
 элементов в структуру данных из последовательного потока. Проверить работу
 шаблона на разра- ботанном классе, используя его как параметр шаблона.
 Структура данных: односвязный список, элемент списка хранит непосредственно
 объект.
 */
#include "list.h"
#include <iostream>

int main()
{
	[[maybe_unused]] int nums[]{1, 4, 8, 8};
	try {
		List<int> l{ };
		for (int i = 4; i > 0; --i)
			l.push(nums[i - 1]);
		while (l.size()) {
			std::cout << l.shift() << ' ';
		}
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
	std::cout << std::endl;
	return 0;
}
