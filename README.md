# Philosopher

Bu proje, birçok felsefeci (philosopher) problemini simüle etmeyi amaçlar. Bu projede, felsefecilerin yemek yeme ve düşünme etkinliklerini senkronize etmek gereklidir.

## Proje Açıklaması

- Proje, senkronizasyon mekanizmalarını `THREAD`  `MUTEX`  VE `SEMHAPORE` yönetimini içerir.
- "Philosopher" projesi, bir dizi felsefeci sürecin yemek yeme ve düşünme etkinliklerini senkronize ederek simüle eder.
- Her felsefeci bir çatal ve bir bıçağa sahiptir ve bu araçları kullanarak yemek yer.
- Felsefeciler aynı anda düşünme ve yeme etkinlikleri arasında geçiş yapar.

## Nasıl Çalışır?

1. **Başlatma:** Projeyi derledikten sonra, `./philo` komutuyla programı başlatabilirsiniz.

2. **Argümanlar:** Programı çalıştırırken argümanlar vermelisiniz. Örneğin: `./philo 4 410 200 200`.

3. **Felsefeciler:** Program belirttiğiniz sayıda felsefeci süreci oluşturur. Felsefeciler bir masada oturur ve yemek yerler.

4. **Senkronizasyon:** Felsefeciler, yemek yeme ve düşünme etkinlikleri arasında senkronize bir şekilde geçiş yaparlar.

5. **Bitirme:** Felsefeciler belirli bir sayıda yemek yedikten sonra program otomatik olarak sonlanır.

## Ayağa Kaldırma Adımları

1. Projeyi indirin.

2. İndirdiğiniz kaynak kodları bir dizine çıkarın.

3. Terminale gidin ve projenin ana dizinine gidin:

    ```bash
    cd /path/to/philosophers
    ```

4. Projeyi derlemek için aşağıdaki komutları kullanabilirsiniz:

    ```bash
    make
    ```

    Bu komut, projeyi derleyecek ve "philo" adlı bir yürütülebilir dosya oluşturacaktır.

5. Programı belirtilen argümanlarla çalıştırmak için aşağıdaki komutu kullanabilirsiniz:

    ```bash
    ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional_number_of_times_each_philosopher_must_eat]
    ```

    Argümanları kendiniz belirleyin. Örneğin: `./philo 4 410 200 200` veya `./philo 5 800 200 200 7`.

6. Projeyi temizlemek için aşağıdaki komutu kullanabilirsiniz:

    ```bash
    make clean
    ```

7. Projeyi sıfırlamak için aşağıdaki komutu kullanabilirsiniz:

    ```bash
    make fclean
    ```

Bu adımları izleyerek "Philosopher" projesini derleyebilir ve çalıştırabilirsiniz.
