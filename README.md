ESP8266 Captive Portal Web Login
Bu proje, ESP8266 (NodeMCU) kartı kullanarak sahte bir Wi-Fi giriş (login) sayfası oluşturur. Cihaz, kendi Wi-Fi ağı olan captiveWeb isimli bir erişim noktası oluşturur. Bağlanan kullanıcılar, otomatik olarak bir oturum açma sayfasına yönlendirilir. Sayfada kullanıcıdan e-posta ve şifre bilgisi istenir.

Form gönderildiğinde, girilen bilgiler ESP8266'nın seri portuna yazdırılır. Veriler herhangi bir yere kaydedilmez veya gönderilmez. Proje tamamen yerel çalışır.

DNS yönlendirmesi sayesinde, kullanıcılar herhangi bir siteye girmeye çalışsa da otomatik olarak bu giriş ekranına yönlendirilir. Bu sayede captive portal etkisi yaratılır.

Proje, özellikle ESP8266 ile çalışan ağ yönlendirme, captive portal ve basit HTML form işlemleri gibi konuları öğrenmek isteyenler için uygundur. Güvenlik testleri, sunumlar veya sadece eğlence amaçlı denenebilir.

Tüm kodlar Arduino IDE üzerinde çalışacak şekilde yazılmıştır. Kod basit ve kolayca düzenlenebilir yapıdadır.

Bu proje sadece test ve eğitim amaçlı olup, kullanılması taktirde yasal sorumluluk tamamen kullanıcıya aittir. 
