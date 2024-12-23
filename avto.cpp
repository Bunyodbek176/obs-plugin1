#include <obs-module.h>
#include <thread>
#include <chrono>

// Plagin haqida ma'lumot
OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("auto_stream_plugin", "en-US")

// Asosiy jarayonni boshqaruvchi funksiya
void start_stop_streaming_cycle()
{
    while (true)
    {
        // Nachat translyatsiyu
        blog(LOG_INFO, "Starting Stream...");
        obs_frontend_streaming_start();
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Upravlyat translatsiyu vaqt ketishi uchun kutish
        
        // Sozdat translatsiyu i nachat efir
        blog(LOG_INFO, "Creating and Starting the Stream...");
        std::this_thread::sleep_for(std::chrono::seconds(5)); // OBS jarayoni boshlanadi

        // 5 daqiqa davomida translyatsiya
        blog(LOG_INFO, "Stream is live for 5 minutes...");
        std::this_thread::sleep_for(std::chrono::minutes(5));

        // Ostanovit translyatsiyu
        blog(LOG_INFO, "Stopping the Stream...");
        obs_frontend_streaming_stop();
        std::this_thread::sleep_for(std::chrono::seconds(5)); // "Da" tugmasi

        blog(LOG_INFO, "Confirm Stop...");
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Yana kutish

        blog(LOG_INFO, "Restarting Stream...");
    }
}

// Plaginni yuklash funksiyasi
bool obs_module_load(void)
{
    blog(LOG_INFO, "Auto Stream Plugin Loaded!");
    std::thread(start_stop_streaming_cycle).detach();
    return true;
}