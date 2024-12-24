# Mail_from_ESP32
This project demonstrates the use of an ESP32 (or ESP8266) microcontroller to send emails using the Simple Mail Transfer Protocol (SMTP). By integrating the ESP_Mail_Client library, the code connects to a Wi-Fi network, authenticates with an SMTP server (e.g., Gmail), and sends an email to a specified recipient. The setup includes configuring Wi-Fi credentials, SMTP server details, and email content. The email message is composed with a subject and body text, and is sent once a successful connection and authentication with the SMTP server are established. Additionally, the code provides callback functions to monitor the email sending status, ensuring reliable email delivery and offering detailed logging information. This project showcases a practical application of IoT devices for real-time communication and alerts.

 Install the library: ESP-Mail-Client library.
Create a new mail ID at the following site: 
https://www.google.com/gmail/about/
3. Create an App password:
An app password can only be used with accounts that have 2-step verification turned on. 
Open your Google Account.
In the search panel, select Security.
Under “Signing in to Google,” select 2-Step Verification > Get started.
After enabling 2-step verification, you can create an app password.
Open your Google Account.
In the search panel, search for App Passwords.
Open the App Passwords menu.
Compile and upload the code onto the ESP32 board.
Go the serial monitor and check if the output is same as that of in the picture.
If yes, check your mail and see if a message has been delivered by ESP32



