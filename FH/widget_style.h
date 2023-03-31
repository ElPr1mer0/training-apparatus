#ifndef WIDGET_STYLE_H
#define WIDGET_STYLE_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTextBrowser;
class QCustomPlot;
class QComboBox;
class QGroupBox;
class QToolBox;

class WIDGET_STYLE: public QWidget{
    Q_OBJECT

public:
    /// ОКНО РЕГИСТРАЦИИ///
    void SetPasswordLineEditStyle(QLineEdit*); // Стиль line edit для окна регистрации и ОКНА ВХОДА тоже(логин)
    void SetLoginLineEditStyle(QLineEdit*); // Стиль line edit для окна регистрации и ОКНА ВХОДА тоже(пароль)
    void SetLabWelcomeStyle(QLabel*); //
    void SetButSignInStyle(QPushButton*);
    void SetButRegistrationStyle(QPushButton*);
    void SetRegistryWindowStyle(QWidget*);//стиль окна регистрации
    /// ОКНО РЕГИСТРАЦИИ///

    ///ОКНО ВХОДА///
    void SetSignInWindowStyle(QWidget*);//стиль окна входа
    void SetButSignInStyle2(QPushButton*);//стиль кнопки войти
    void SetButBackStyle(QPushButton*);
    ///ОКНО ВХОДА///

    ///ОКНО HOME///
    void SetHomeWindowStyle(QWidget*);
    void SetTBHomePanelStyle(QToolBox *);
    ///ОКНО HOME///


    ///ОКНО ПЕЧАТИ///
    void SetPrintSpeedWindowStyle(QWidget*);
    void SetTextBrowserStyle(QTextBrowser*);
    void SetPlotSpeedStyle(QCustomPlot*);
    void SetPlotMistakeStyle(QCustomPlot*);
    void SetPlotAmountTextStyle(QCustomPlot*);
    void SetBoxsYearsStyle(QComboBox*);
    void SetBoxsMonthsStyle(QComboBox*);
    void SetGroupPlotStyle(QGroupBox*);

    ///ДОП ОКНО СОЗДАНИЯ ТРЕНИРОВКИ///
    void SetCreateTrainingWindowStyle(QWidget*);
    void SetLdGeneralTrainingWindowStyle(QLineEdit*); //Если General то под стиль нескольких компанентов совпадает
    void SetLdCurrentSymbolsStyle(QLineEdit*);
    void SetLabAddRulesStyle(QLabel*);
    void SetLabGeneralTrainingWindowStyle(QLabel*);
    void SetLabStatusStyle(QLabel*);
    void SetButGeneralTrainingWindwowStyle(QPushButton*);
    void SetBrowserTrainingWordStyle(QTextBrowser*);
    ///ДОП ОКНО СОЗДАНИЯ ТРЕНИРОВКИ///

    ///ОКНО ПЕЧАТИ///


    ///ОКНО ТЕСТА НА РЕАКЦИЮ///
    void SetReactionSpeedWindowStyle(QWidget*);
    void SetButReactionSpeedStyle(QPushButton*);
    void SetButReactionSpeedCanClickStyle(QPushButton*);
    void SetLabInfoStyle(QLabel*);
    void SetLabResultStyle(QLabel*);
    ///ОКНО ТЕСТА НА РЕАКЦИЮ///
};

#endif // WIDGET_STYLE_H
