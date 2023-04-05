import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders

fromaddr = "bhatganesh021@gmail.com"
toaddr = "shruthisas7@gmail.com"

# instance of MIMEMultipart
ms = MIMEMultipart()

# storing the senders email address
ms['From'] = fromaddr

# storing the receivers email address
ms['To'] = toaddr

# storing the subject
ms['Subject'] = "Testmail"

# string to store the body of the mail
body = "see this"

# attach the body with the msg instance
ms.attach(MIMEText(body, 'plain'))

# open the file to be sent
filename = "HPF.xlsx"
attachment = open(r"G:\Excel sheet\HPF.xlsx", "rb")


# instance of MIMEBase and named as p
p = MIMEBase('application', 'octet-stream')

# To change the payload into encoded form
p.set_payload((attachment).read())

# encode into base64
encoders.encode_base64(p)

p.add_header('Content-Disposition', "attachment; filename= %s" % filename)

# attach the instance 'p' to instance 'msg'
ms.attach(p)

# creates SMTP session
s = smtplib.SMTP('smtp.gmail.com', 587)

# start TLS for security
s.starttls()

# Authentication
s.login(fromaddr,"ganeshbhat1234")

# Converts the Multipart msg into a string
text = ms.as_string()

# sending the mail
s.sendmail(fromaddr, toaddr, text)

# terminating the session
s.quit()