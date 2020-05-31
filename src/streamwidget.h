#ifndef STREAMWIDGETS_H
#define STREAMWIDGETS_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class StreamWidget;
}

class StreamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StreamWidget(QWidget *parent = nullptr);
    ~StreamWidget();
    QJsonObject getSettings();
    void setSettings(const QJsonObject &st);

private slots:
    void on_transportCombo_currentIndexChanged(int index);

    void on_transportCombo_currentIndexChanged(const QString &arg1);

    void on_tcpHeaderTypeCB_currentIndexChanged(const QString &arg1);

    void on_tcpRequestTxt_textChanged();

    void on_tcpRespTxt_textChanged();

    void on_httpPathTxt_textEdited(const QString &arg1);

    void on_httpHostTxt_textChanged();

    void on_wsHeadersTxt_textChanged();

    void on_wsPathTxt_textEdited(const QString &arg1);

    void on_kcpMTU_valueChanged(int arg1);

    void on_kcpTTI_valueChanged(int arg1);

    void on_kcpUploadCapacSB_valueChanged(int arg1);

    void on_kcpCongestionCB_stateChanged(int arg1);

    void on_kcpDownCapacitySB_valueChanged(int arg1);

    void on_kcpReadBufferSB_valueChanged(int arg1);

    void on_kcpWriteBufferSB_valueChanged(int arg1);

    void on_kcpHeaderType_currentTextChanged(const QString &arg1);

    void on_quicSecurityCB_currentTextChanged(const QString &arg1);

    void on_quicKeyTxt_textEdited(const QString &arg1);

    void on_quicHeaderTypeCB_currentIndexChanged(const QString &arg1);

    void on_tlsCB_stateChanged(int arg1);

    void on_allowInsecureCB_stateChanged(int arg1);

    void on_allowInsecureCiphersCB_stateChanged(int arg1);

    void on_serverNameTxt_textEdited(const QString &arg1);

    void on_alpnTxt_textChanged();

private:
    Ui::StreamWidget *ui;
    QJsonObject settings;
};

#endif // STREAMWIDGETS_H
