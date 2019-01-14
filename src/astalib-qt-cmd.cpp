#include <QCoreApplication>
#include <QSocketNotifier>
#include <iostream>
#include <QDebug>

void printCommands()
{
    std::cout << "#-----------------#" << std::endl;
    std::cout << "Commands available:" << std::endl;
    std::cout << " start"                   << "\t\t\t\tStarts a task and prints its ID." << std::endl;
    std::cout << " start <task_type_id>"    << "\t\tStarts a task of a given type and prints its ID." << std::endl;
    std::cout << " pause <task_id>"         << "\t\tPause the task with the given ID and print a confirmation message." << std::endl;
    std::cout << " resume <task_id>"        << "\t\tResume task with the given ID (if paused) and print a confirmation message." << std::endl;
    std::cout << " stop <task_id>"          << "\t\t\tStop the task with the given ID (if not stopped) and print a confirmation message." << std::endl;
    std::cout << " status"                  << "\t\t\t\tPrints the ID, type ID, the status (paused, running, stopped, completed) and an optional indicator of progress for each task." << std::endl;
    std::cout << " status <task_id>"        << "\t\tPrints the ID, type ID, the status (paused, running, stopped, completed) and an optional indicator of progress for the task with the given ID." << std::endl;
    std::cout << " quit"                    << "\t\t\t\tQuit gracefully." << std::endl;
    std::cout << "#-----------------#" << std::endl;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QStringList args = app.arguments();
    if(args.size() > 1)
    {
        // No need to check if arg[1] is help or not. Just print it anyways
        std::cout << "Usage: " << args[0].toStdString() << "" << std::endl;
        std::cout << "Program will be launched and waiting for commands from the standard input" << std::endl;
        printCommands();
        return 0;
    }

    QSocketNotifier notifier(fileno(stdin), QSocketNotifier::Read );
    QObject::connect(&notifier, &QSocketNotifier::activated, [&app](int)
    {
        QTextStream qtin(stdin); 
        QString line = qtin.readLine();

        QStringList inputCmd = line.split(' ');
        if(inputCmd.size() > 0 && inputCmd.size() <= 2)
        {
            if(inputCmd[0] == "start")
            {
                std::cout << "START" << std::endl;
            }
            else if(inputCmd[0] == "pause")
            {
                std::cout << "PAUSE" << std::endl;
            }
            else if(inputCmd[0] == "resume")
            {
                std::cout << "RESUME" << std::endl;
            }
            else if(inputCmd[0] == "stop")
            {
                std::cout << "STOP" << std::endl;
            }
            else if(inputCmd[0] == "status")
            {
                std::cout << "STATUS" << std::endl;
            }
            else if(inputCmd[0] == "quit")
            {
                std::cout << "QUIT" << std::endl;
            }
            else
            {
                printCommands();
            }
        }
        else
        {
            printCommands();
        }
    });
    
    app.exec();
    // Cleanup before leaving
}