#include <QCoreApplication>
#include <QSocketNotifier>
#include <iostream>
#include <QDebug>

int main(int argc, char **argv)
{
    // TODO: Read the args.
    // The command line arguments which are passed to QCoreApplication's constructor should be accessed using the arguments() function.

    QCoreApplication app(argc, argv);

    QSocketNotifier notifier(fileno(stdin), QSocketNotifier::Read );
    QObject::connect(&notifier, &QSocketNotifier::activated, [&app](int socket)
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
                std::cout << "Wrong command: " << line.toStdString() << std::endl;
                // TODO print help
            }
        }
        else
        {
            std::cout << "Wrong command: " << line.toStdString() << std::endl;
            // TODO print help
        }
    });
    
    app.exec();
    // Cleanup before leaving
}