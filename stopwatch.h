/**
 * @file stopwatch.h
 * @brief Консольный секундомер
 */

#pragma once

#include <chrono>

namespace TrafficGenerator 
{

/**
 * @brief Класс со значениями времени
 */
class StpwtchTime 
{
public:
    int us; /*!< Значение микросекунд */

    int ms; /*!< Значение милиросекунд */

    int s;  /*!< Значение секунд */

    int min; /*!< Значение минут */

    int hour; /*!< Значение часов */
};

/**
 * @brief Класс секундомера
 */
class Stopwatch 
{
private:
    bool isFromStopToStart; /*!< Флаг запуска после остановки */

    bool isWorked;  /*!< Флаг того, что секундомер запущен */

    bool isStopped; /*!< Флаг того, что секундомер остановлен */

    long deltaTime; /*!< Разница между предыдущим значением времени и текущем */

    StpwtchTime time; /*!< Значение времени */

    struct timespec deltaStop; /*!< Разница между текущем временем и временем остановки */

    struct timespec stopTime; /*!< Временем остановки */

    struct timespec startTime; /*!< Временем запуска */

    struct timespec curTime; /*!< Текущее время */

    /**
     * @brief Преобразовать struct timespec в StpwtchTime
     */
    void conversion ();
    
public:
    /**
     * @brief Конструктор
     */
    Stopwatch ();

    /**
     * @brief Запустить секундомер
     */
    void start ();

    /**
     * @brief Вернуть время в формате класса StpwtchTime
     */
    StpwtchTime get ();

    /**
     * @brief Сбросить текущее значение времени
     */
    void reset ();

    /**
     * @brief Остановить
     */
    void stop ();
};

} /// namespace TrafficGenerator
