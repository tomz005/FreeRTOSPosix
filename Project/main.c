/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*
 * main() creates all the demo application tasks, then starts the scheduler.
 * The web documentation provides more details of the standard demo application
 * tasks, which provide no particular functionality but do provide a good
 * example of how to use the FreeRTOS API.
 *
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Check" task - This only executes every five seconds but has a high priority
 * to ensure it gets processor time.  Its main function is to check that all the
 * standard demo tasks are still operational.  While no errors have been
 * discovered the check task will print out "OK" and the current simulated tick
 * time.  If an error is discovered in the execution of a task then the check
 * task will print out an appropriate error message.
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h" /* RTOS firmware */
#include "task.h"     /* Task */
#include "timers.h"
//#include "queue.h"
/* Examples */
#define CH3_TASKMANAGEMENT

/* --------------------------------------------- */
#ifdef CH3_TASKMANAGEMENT
void vTask1(void *);
void vTask2(void *);
void vTask3(void *);
void vTask4(void *);
void vTask5(void *);
void vTask6(void *);
void vTask7(void *);
void vTask8(void *);

#endif

void vApplicationIdleHook(void);
static int counter4 = 0;
static int counter5 = 0;
static int counter6 = 0;
static int counter7 = 0;
int main(void)
{
    int deadline1 = 130;
    int deadline2 = 140;
    int deadline3 = 200;
#ifdef CH3_TASKMANAGEMENT
    /*FIFO SCHEDULING*/
    // xTaskCreate(vTask1, "Task 1", 1000, &deadline1, 2, NULL);
    // xTaskCreate(vTask2, "Task 2", 1000, &deadline2, 1, NULL);
    // xTaskCreate(vTask3, "Task 3", 1000, &deadline3, 3, NULL);

    /*SJF Scheduling*/
    xTaskCreate(vTask4, "Task 4", 1000, NULL, 4, NULL);
    xTaskCreate(vTask5, "Task 5", 1000, NULL, 2, NULL);
    xTaskCreate(vTask6, "Task 6", 1000, NULL, 3, NULL);
    xTaskCreate(vTask7, "Task 7", 1000, NULL, 1, NULL);
#endif

    vTaskStartScheduler();
    return 0;
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName)
{
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}

#ifdef CH3_TASKMANAGEMENT
void vTask1(void *parameter)
{
    // printf("%d\n", pdMS_TO_TICKS(4));

    // printf("parameter : %d\n", deadline);
    vTaskDelay(pdMS_TO_TICKS(40));
    int deadline = *((int *)parameter);
    TickType_t startTime = xTaskGetTickCount();
    printf("T1 -> Start time : %0.3fms\n", (startTime / 10.0));
    // while (1)
    // {
    // printf("Task 1\n");
    // vTaskDelay(pdMS_TO_TICKS(250));
    // }
    int flag = 0;
    for (;;)
    {
        TickType_t curtime = xTaskGetTickCount();
        // printf("Loop time : %dms\n", curtime);
        if (curtime >= deadline && !flag)
        {
            flag = 1;
            printf("Deadline Violation for T1\n");
        }
        if (curtime >= (startTime + 70))
            break;
    }
    // printf("Executed for %d loops\n", i);
    TickType_t endTime = xTaskGetTickCount();
    printf("T1 -> End time : %0.3fms\n", (endTime / 10.0));
    vTaskDelete(NULL);
}
void vTask2(void *parameter)
{
    vTaskDelay(pdMS_TO_TICKS(90));
    int deadline = *((int *)parameter);
    TickType_t startTime = xTaskGetTickCount();
    printf("T2 -> Start time : %0.3fms\n", (startTime / 10.0));
    // while (1)
    // {
    // printf("Task 2\n");
    // vTaskDelay(pdMS_TO_TICKS(250));
    // }
    // int i = 0;
    int flag = 0;
    for (;;)
    {
        TickType_t curtime = xTaskGetTickCount();
        // printf("Loop time : %dms\n", curtime);
        if (curtime >= deadline && !flag)
        {
            flag = 1;
            printf("Deadline Violation for T2\n");
        }

        if (curtime >= (startTime + 20))
            break;
    }
    // printf("Executed for %d loops\n", i);
    TickType_t endTime = xTaskGetTickCount();
    printf("T2 -> End time : %0.3fms\n", (endTime / 10.0));
    vTaskDelete(NULL);
}
void vTask3(void *parameter)
{
    // TickType_t xLastWaketime = xTaskGetTickCount();
    vTaskDelay(pdMS_TO_TICKS(30));
    int deadline = *((int *)parameter);
    TickType_t startTime = xTaskGetTickCount();
    printf("T3 -> Start time : %0.3fms\n", (startTime / 10.0));
    // while (1)
    // {
    // printf("Task 3\n");
    // vTaskDelayUntil(&xLastWaketime, pdMS_TO_TICKS(6));
    // }
    // int i = 0;
    int flag = 0;
    for (;;)
    {
        TickType_t curtime = xTaskGetTickCount();
        // printf("Loop time : %dms\n", curtime);
        if (curtime >= deadline && !flag)
        {
            flag = 1;
            printf("Deadline Violation for T3\n");
        }
        if (curtime >= (startTime + 25))
            break;
    }
    // printf("Executed for %d loops\n", i);
    TickType_t endTime = xTaskGetTickCount();
    printf("T3 -> End time : %0.3fms\n", (endTime / 10.0));
    vTaskDelete(NULL);
}
void vTask8(void *parameter)
{
    TickType_t xLastWaketime = xTaskGetTickCount();
    while (1)
    {
        printf("Task 8 with 500ms\n");
        // vTaskDelayUntil(&xLastWaketime, pdMS_TO_TICKS(500));
    }
}
void vTask4(void *parameter)
{
    // printf("%d\n", pdMS_TO_TICKS(4));
    // vTaskDelay(pdMS_TO_TICKS(4));

    TickType_t startTime = xTaskGetTickCount();
    // printf("%d\n", startTime);

    TickType_t curtime;
    printf("T1 -> Start time : %dms\n", startTime);
    while (1)
    {
        vTaskPrioritySet(NULL, 5);
        counter4++;
        // printf("%d\n", counter4);
        TickType_t LastwakeTime = xTaskGetTickCount();
        printf("T1 : %d\n", LastwakeTime);
        for (;;)
        {
            curtime = xTaskGetTickCount();
            if (curtime >= (LastwakeTime + 3))
                break;
        }
        vTaskPrioritySet(NULL, 4);
        // printf("%d.....\n", curtime);
        if (counter4 == 1)
        {
            printf("Job 1 of Task1 completed : %d\n", curtime);
            printf("Response Time of Task1 : %dms\n", curtime);
            printf("------------------------\n");
            // exit(0);
        }
        // curtime = xTaskGetTickCount();
        // printf("Sleep time : %d\n", 8 * counter4 - curtime);
        if (8 * counter4 > curtime)
            vTaskDelayUntil(&curtime, pdMS_TO_TICKS(8 * counter4 - curtime));
        // else
        //     //     vTaskDelayUntil(&curtime, pdMS_TO_TICKS(0));
        //     printf("No sleep\n");
    }
}
void vTask5(void *parameter)
{
    TickType_t startTime = xTaskGetTickCount();
    // printf("%d\n", startTime);

    TickType_t curtime;
    printf("T2 -> Start time : %dms\n", startTime);
    while (1)
    {
        vTaskPrioritySet(NULL, 5);
        counter5++;
        // printf("counter5 %d\n", counter5);
        TickType_t LastwakeTime = xTaskGetTickCount();
        printf("T2 : %d\n", LastwakeTime);
        for (;;)
        {
            curtime = xTaskGetTickCount();
            if (curtime >= (LastwakeTime + 8))
                break;
        }

        // printf("%d.....\n", curtime);
        if (counter5 == 1)
        {
            printf("Job 1 of Task2 completed : %d\n", curtime);
            printf("Response Time of Task2 : %dms\n", curtime);
            printf("------------------------\n");
        }
        vTaskPrioritySet(NULL, 2);
        // curtime = xTaskGetTickCount();
        // printf("T2 sleep :%d\n", 15 * counter5 - curtime);
        if (15 * counter5 > curtime)
            vTaskDelayUntil(&curtime, pdMS_TO_TICKS(15 * counter5 - curtime));
    }
    // vTaskDelete(NULL);
}
void vTask6(void *parameter)
{
    TickType_t startTime = xTaskGetTickCount();
    // printf("%d\n", startTime);

    TickType_t curtime;
    printf("T3 -> Start time : %dms\n", startTime);
    while (1)
    {
        vTaskPrioritySet(NULL, 5);
        counter6++;
        // printf("%d\n", counter);
        TickType_t LastwakeTime = xTaskGetTickCount();
        printf("T3 : %d\n", LastwakeTime);
        for (;;)
        {
            curtime = xTaskGetTickCount();
            if (curtime >= (LastwakeTime + 4))
                break;
        }

        // printf("%d.....\n", curtime);
        if (counter6 == 1)
        {
            printf("Job 1 of Task3 completed : %d\n", curtime);
            printf("Response Time of Task3 : %dms\n", curtime);
            printf("------------------------\n");
        }
        vTaskPrioritySet(NULL, 3);
        // curtime = xTaskGetTickCount();
        if (20 * counter6 > curtime)
            vTaskDelayUntil(&curtime, pdMS_TO_TICKS(20 * counter6 - curtime));
    }
}
void vTask7(void *parameter)
{

    TickType_t startTime = xTaskGetTickCount();
    // printf("%d\n", startTime);

    TickType_t curtime;
    printf("T7 -> Start time : %dms\n", startTime);
    while (1)
    {
        vTaskPrioritySet(NULL, 5);
        counter7++;
        // printf("%d\n", counter);
        TickType_t LastwakeTime = xTaskGetTickCount();
        printf("T7 : %d\n", LastwakeTime);
        for (;;)
        {
            curtime = xTaskGetTickCount();
            if (curtime >= (LastwakeTime + 10))
                break;
        }

        // printf("%d.....\n", curtime);
        if (counter7 == 1)
        {
            printf("Job 1 of task7 completed : %d\n", curtime);
            exit(0);
        }
        vTaskPrioritySet(NULL, 1);
        // curtime = xTaskGetTickCount();
        if (22 * counter7 > curtime)
            vTaskDelayUntil(&curtime, pdMS_TO_TICKS(22 * counter7 - curtime));
    }
}
#endif
/* CH3_TASKMANAGEMENT ends */

void vApplicationIdleHook(void)
{
    //	printf("Idle\r\n");
}
/*-----------------------------------------------------------*/
