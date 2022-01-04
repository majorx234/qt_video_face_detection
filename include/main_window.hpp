#ifndef MAIN_WINDOW_HPP 
#define MAIN_WINDOW_HPP

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open();
    bool save();

private:
    void createMenuBar();
    void createStatusBar();
    bool saveFile(const QString &fileName);


};        

#endif // MAIN_WINDOW_HPP