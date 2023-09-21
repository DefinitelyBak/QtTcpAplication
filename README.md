# Проект 3D-визуализации лопатки двигателя.

<img src = "image/image1.png">


**Цель работы:** визуализировать лопатку двигателя по входному множеству точек передаваемые в виде json файла.

В данном проекте используется топлогия 3D объектов представленных в OpenCascade. Для построения поверхности спинки и корыта лопадки используются поверхности Безье.

**Программа состоит из классов:**

1. occQt - класс главного окна.
2. OccView - класс сцены, отвечающий за отображение 3D-объектов, взимодействие с openGl.
3. jsonReader - класс отвечающий за чтение и парсинг json файла.
4. builderAisShape - класс отвечающий за построение 3D объекта лопадки по значениям полученным из класса jsonReader.