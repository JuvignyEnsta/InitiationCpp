#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <condition_variable>
#include <iomanip>

const char* strEmpty = "(empty)";

struct Foo
{
    bool triggerBanner{false};
    char const* pt_bannerToCopy{strEmpty};
    std::string   banner{};

    void declenche(char const* t_banner)
    {
        pt_bannerToCopy = t_banner;
        triggerBanner  = true;
    }

    void setValueOnTrigger()
    {
        while(!triggerBanner) {}
        banner = std::string(pt_bannerToCopy);
    }
};

struct VolatileFoo
{
    volatile bool triggerBanner{false};
    char const* pt_bannerToCopy{strEmpty};
    std::string   banner{};

    void declenche(char const* t_banner)
    {
        pt_bannerToCopy = t_banner;
        triggerBanner  = true;
    }

    void setValueOnTrigger()
    {
        while(!triggerBanner) {}
        banner = std::string(pt_bannerToCopy);
    }
};


struct AtomicFoo
{
    std::atomic_bool triggerBanner{false};
    std::atomic<char const*> pt_bannerToCopy{strEmpty};
    std::string   banner{};

    void declenche(char const* t_banner)
    {
        pt_bannerToCopy.store(t_banner);
        triggerBanner.store(true);
    }

    void setValueOnTrigger()
    {
        while (!triggerBanner.load()) {}
        banner = std::string(pt_bannerToCopy.load());
    }
};

struct AcquireReleaseFoo
{
    std::atomic_bool triggerBanner{false};
    std::atomic<char const*> pt_bannerToCopy{strEmpty};
    std::string   banner{};

    void declenche(char const* t_banner)
    {
        pt_bannerToCopy.store(t_banner, std::memory_order::release);
        triggerBanner.store(true, std::memory_order::release);
    }

    void setValueOnTrigger()
    {
        while (!triggerBanner.load(std::memory_order::acquire)) {};
        banner = std::string(pt_bannerToCopy.load(std::memory_order::acquire));
    }
};

struct RelaxedFoo
{
    std::atomic_bool triggerBanner{false};
    std::atomic<char const*> pt_bannerToCopy{strEmpty};
    std::string   banner{};

    void declenche(char const* t_banner)
    {
        pt_bannerToCopy.store(t_banner, std::memory_order::relaxed);
        triggerBanner.store(true, std::memory_order::relaxed);
    }

    void setValueOnTrigger()
    {
        while (!triggerBanner.load(std::memory_order::relaxed)) {};
        banner = std::string(pt_bannerToCopy.load(std::memory_order::relaxed));
    }
};

struct CondVarFoo
{
    std::condition_variable cv;
    std::mutex              triggerLock;
    char const* pt_bannerToCopy{strEmpty};
    std::string   banner{};

    void declenche(char const* t_banner)
    {
        cv.notify_one();
        std::unique_lock lk(triggerLock);
        pt_bannerToCopy = t_banner;
        cv.notify_one();
    }

    void setValueOnTrigger()
    {
        std::unique_lock lk(triggerLock);
        cv.wait(lk, [this] { return pt_bannerToCopy != strEmpty; });
        banner = std::string(pt_bannerToCopy);
        lk.unlock();
    }
};


template<typename F>
void test(std::string const& label )
{
    std::string a_banner{"Welcome in the multithreaded world !"};
    constexpr int nbSamples = 1000;
    int nbSuccess = 0;
    auto debut = std::chrono::high_resolution_clock::now();
    for (int i{0}; i<nbSamples; ++i)
    {
        //std::cout << "Sample " << std::setw(4) << i; 
        F foo;
        std::thread t1(&F::declenche, &foo, a_banner.c_str());
        std::thread t2(&F::setValueOnTrigger, &foo);
        t1.join(); t2.join();
        if (foo.banner == a_banner) ++nbSuccess;
        //std::cout << "\r";
    }
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duree = fin - debut;
    std::cout << label << " a réussi " << nbSuccess << "/"
              << nbSamples << " fois en "
              << duree.count() << std::endl;
}

int main()
{
    test<Foo>("Test avec booléen C++");
    test<VolatileFoo>("Test avec volatile C++");
    test<AtomicFoo>("Test avec atomiques C++");
    test<AcquireReleaseFoo>("Test avec atomic acquire/release"); 
    test<RelaxedFoo>("Test avec atomic relaxed"); 
    test<CondVarFoo>("Test avec variable conditionnelle"); 
    return EXIT_SUCCESS;
}
