# Программа для расчёта норм расхода материала

Данная программа предназначена для расчёта норм расхода материалов, которые расходуются при выполнении какого-либо технологического процесса.   
Как правило, норма расхода материала линейно зависит от заданого значения технологического параметра, например от площади покрытия или массы детали. В редких случаях зависимость может быть от двух и более параметров.
Поэтому расчёт в подавляющем числе случаев можно свести к произведению некоторого коэффициента на значение параметра (или нескольких параметров) технологического процесса.  
Исходные данные по которым можно рассчитать норму расхода для технологического процесса записываются в текстовом файле по определённым правилами (см. ниже). На основании этих данных создаётся пользовательский интерфейс для расчёта норм.  
Графический интерфейс пользователя разработан с применением фреймворка Qt.  
По умолчанию все текстовые файлы с данными должны содержаться в папке `/data` в корне с программой.

## Правила записи исходных данных норм расхода

Исходные данные норм расхода материалов представляют собой список материалов с указанием названия материала, удельной нормы расхода и какие единицы измерений используются. Списки материалов должны быть разбиты по техпроцессам и операциям. Все объявления техпроцессов, операций и материалов должны записываться одной строкой, разбиение на разные строки не допускается.   
Запись данных должна начинаться с объявления техпроцесса с помощью ключевого слова `ТЕХПРОЦЕСС` (регистр не важен), после которого следует название техпроцесса, все записи до этого ключевого слова игнорируются.  
Все записи после объявления техпроцесса считаются частью этого техпроцесса до тех про пока не встретится другое объявление техпроцесса. В одном текстовом файле может быть задано любое количество техпроцессов.  
Внутри техпроцесс разбивается на технологические операции (должна быть хотя бы одна), а те материалы которые вписаны вне операции игнорируются.
Объявления операции должно начинаеться с трёх цифр и разделяться пробелом с последующим текстом, который считается названием операции. Если требуется записать материал название которого начинается с трёх цифр и пробела, то рекомендуется поставить пробел перед названием, при парсинге, пробел отбросится, но строка не будет рассматриваться как объявление операции. Внутри техпроцесса может быть неограниченное количество операций. Все записи после объявления операции считаются операции до тех пор как не встретится объявление другой операции или техпроцесса.  

Пример объявление техпроцесса и операции в нём:  

    Техпроцесс   Цинкование
    005 Обезжиривание
После объявление техпроцесса и операции можно вносить записи норм расхода. Например:

    Уайт-спирит   ГОСТ 3134-78      0,2  мл/г
    Нитрит натрия ГОСТ 19906-74     0,4  г/дм2 * 1 мкм(толщина покрытия) 

Где `Уайт-спирит ГОСТ 3134-78` и `Нитрит натрия ГОСТ 19906-74` &mdash; это название материала (вместе с нормативным документом на него); `0,2` и `0,4` &mdash; это это удельные нормы расхода, коэффициенты, через которые вычисляются нормы расхода.   
Далее, следуют единицы измерения разделённых слешем `мл/г` и `г/дм2`:  
первая единица &mdash; это та единица в которой расcчитывается норма расхода;   
вторая единица &mdash; это единица измерения параметра от которого зависит норма.  
Наконец, следует третья единица измерения, со своим коэффициентом, они отделяются символами `/` или `*`. Если не перед третьей единицей не выставить никакое значение, то коэффициент по умолчанию будет равен 1.
В скобках указывается уникальное имя параметра (длинна не более 30 символов), оно требуется в том случае, если в техпроцессе есть несколько параметров с единицами измерения одного типа:

    Отвердитель №1    0.1 г / мл(объём компаунда) / мл(объём герметика)

В этом случае создадутся две уникальные единицы измерения `мл(объём компаунда)` и `мл(объём герметика)` от них будут зависеть только те материалы, у которых в описании прямо указаны единицы измерения с этими же именами.   
Так же, две записи материала могут быть разделены ключевым словом `ИЛИ` в этом случае эти материалы будут считаться взаимозаменяемыми, что будет отражаться в графическом интерфейсе.
`ИЛИ` должно быть записано одной строкой, без пробелов и каких-либо символов.  
## Расчёт нормы расхода

Расчёт нормы расхода производится по следующей формуле:

    коэффициент1 × ввод1 [ × ввод2 / коэффициент2 ],

где `коэффициент1` и `коэффициент2` это коэффиценты удельных норм расхода, пересчитанные под основную единицу поля ввода. Например, единицы длинны для ввода всегда переводятся в метры, а площади  &mdash; в квадратные дециметры.
`ввод1` и `ввод2` пользовательский ввод для параметров.
## Поддерживаемые единицы измерения
На данный момент программа поддерживает следующие единицы измерения:
#### Единицы длинны:
    "м"(метр)    //основная единица ввода
    "см"(сантиметр)
    "мм"("миллиметр")
#### Единицы объёма:
    "м3"(метр кубический)
    "дм3"(дециметр кубический)
    "л"(литр)    //основная единица ввода, численно равно дм3
    "см3"(сантиметр кубический)
    "мл"(миллилитр)
#### Единицы площади:
    "м2"(метр квадратный)
    "см2"(сантиметр квадратный)
    "дм2"(дециметр квадратный)    //основная единица ввода
#### Единицы массы:
    "мг"(миллиграмм)
    "г"(грамм)    //основная единица ввода
    "кг"(килограмм),
    "т"(тонна"),
#### Единицы толщины:
    "мкм"(микрон)    //основная единица ввода

#### Единицы количества:
    "шт"(штук)   
Единица `мкм`(микрон) всегда трактуется как единица толщины, а `мм` всегда как единица длинны.  
Расход материалов которые зависят от единицы `шт` всегда фиксирован, а единица `шт` не получает поле ввода, как как подразумевается, что нормы расхода всегда рассчитываются на одну условную штуку изготавливаемой единицы.  

## Тестирование
Для программы предусмотрен модульный тест корректности работы парсера. Для того, чтобы выполнить сборку теста необходимо при сборке программы добавить для CMake аргумент `-DBUILD_TESTS=ON`. Для работы теста требуется фреймворк Catch2, конфигурация CMake предполагает, что фреймворк установлен в системе.
