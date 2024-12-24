#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>

#define WIFI_SSID "techno"
#define WIFI_PASSWORD "techno@123"
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "shreyasrk647@gmail.com"
#define AUTHOR_PASSWORD "jdil rvqw ureb aqug"
#define RECIPIENT_EMAIL "shreya.s2022a@vitstudent.ac.in"

SMTPSession smtp;

void smtpCallback(SMTP_Status status) {
  Serial.println(status.info());
  if (status.success()) {
    Serial.printf("Message sent success: %d\nMessage sent failed: %d\n", status.completedCount(), status.failedCount());
    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {
      SMTP_Result result = smtp.sendingResult.getItem(i);
      Serial.printf("Message No: %d\nStatus: %s\nDate/Time: %s\nRecipient: %s\nSubject: %s\n", 
        i + 1, result.completed ? "success" : "failed",
        MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str(),
        result.recipients.c_str(), result.subject.c_str());
    }
    smtp.sendingResult.clear();
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(300);
  Serial.printf("Connected with IP: %s\n", WiFi.localIP().toString().c_str());

  MailClient.networkReconnect(true);
  smtp.debug(1);
  smtp.callback(smtpCallback);

  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;

  SMTP_Message message;
  message.sender.name = F("ESP");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("ESP Test Email");
  message.addRecipient(F("Sara"), RECIPIENT_EMAIL);
  message.text.content = "Hello World! - Sent from ESP board";
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  if (smtp.connect(&config) && smtp.isLoggedIn() && smtp.isAuthenticated()) {
    if (!MailClient.sendMail(&smtp, &message)) {
      Serial.printf("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    }
  }
}

void loop() {}
