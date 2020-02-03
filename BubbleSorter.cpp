// BubbleSorter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
class A
{
protected:
	virtual void run()
	{
		init(); // Инициализация
		while (isDone())
			idle(); // Чтото делаем на каждой итерации цикла
		cleanup(); // Освобождаем ресурсы
	}
	// Чистые виртуальные функции
	virtual void init() = 0;
	virtual bool isDone() = 0;
	virtual void idle() = 0;
	virtual void cleanup() = 0;
};
// Астрактный класс для сортировки пузырьком (тип элемента массива не известен)
class BubbleSorter
{
public:
	// Печать массива
	virtual void print(std::ostream & out) = 0;
protected:
	int len = 0; // Число элементов массива
	// Меняем местами в массиве элементы с индексами index и index+1
	virtual void swap(int index) = 0;
	// Возвращает, если элементы с индексами index и index+1, надо поменять местами
	virtual bool outOfOrder(int index) = 0;
	// Собственно сортировка массива
public:
	virtual void doSort()
	{
		for (int i = 0; i < len - 1; i++)
		{
			bool flag=false; // Флаг показывает, что был выполнен обмен элементов 
			for (int j = 0; j < len - 1 - i; j++)
				if (outOfOrder(j)) // Меняем элементы местами
				{
					swap(j);
					flag = true;
				}
			if (!flag) // Замен не было, массив уже отсортирован
				break;
		}

	}
	virtual ~BubbleSorter()
	{
		std::cout << "~BubbleSorter()" << std::endl;
	}
};

// Класс для работы с массивов int
class IntBubbleSorter : public BubbleSorter
{
	int * array = nullptr;
protected:
	void swap(int index)
	{
		int temp = array[index];
		array[index] = array[index + 1];
		array[index + 1]=temp;
	}
	bool outOfOrder(int index)
	{
		if (array[index] > array[index + 1]) return true;
		else return false;
	}
public:
	virtual void print(std::ostream & out)
	{
		for (int i = 0; i < len; i++)
			out << array[i] << ' ';
		out << std::endl;
	}
	// Конструктор копирования
	IntBubbleSorter(IntBubbleSorter & Ob)
	{
		this->len = Ob.len;
		this->array = new int[len];
		for (int i = 0; i < len; i++)
			Ob.array[i] = array[i];
	}

	// Конструктор перемещения
	IntBubbleSorter(IntBubbleSorter && Ob)
	{
		this->len = Ob.len;
		this->array = array;
		Ob.array = nullptr; Ob.len = 0;
		
	}

	IntBubbleSorter(int *array, int len)
	{
		this->len = len;
		this->array = new int[len];
		for (int i = 0; i < len; i++)
			this->array[i] = array[i];
	}
	~IntBubbleSorter()
	{
		if (array != nullptr) delete[] array;
		std::cout << "~IntBubbleSorter()" << std::endl;
	}

};

int main()
{
	int A[] = { 14, 56, 1, 24, 89, 21, 45, 36, 19, 3, 10 };
	IntBubbleSorter Ob1(A, 11);
	Ob1.print(std::cout);
	Ob1.doSort();
	Ob1.print(std::cout);
	BubbleSorter *pOb = new IntBubbleSorter(A, 11);
	pOb->print(std::cout);
	delete pOb;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
