#include <unordered_map>
#include <shared_mutex>
#include <iostream>
#include <optional>
#include <thread>

struct Dictionnaire {
    void addWord( std::string const& mot, std::string const& definition )
    {  accessLock.lock();  m_dico[mot] = definition;  accessLock.unlock();  }
    void getDefinition( std::string const& mot, std::string& def ) const {
        accessLock.lock_shared();
        if (m_dico.find(mot) != m_dico.end()) {
            def = m_dico.at(mot);
            accessLock.unlock_shared();
        } else {
            def = "";
            accessLock.unlock_shared();
        }                                                                }

    using dico_t = std::unordered_map<std::string,std::string>;
    using iterator = typename dico_t::iterator;
    using const_iterator = typename dico_t::const_iterator;
    iterator begin() { return m_dico.begin(); }
    const_iterator begin() const { return m_dico.begin(); }
    iterator end() { return m_dico.end(); }
    const_iterator end() const { return m_dico.end(); }
private:
    static std::shared_mutex accessLock;
    dico_t m_dico;
};

std::shared_mutex Dictionnaire::accessLock;

int main()
{
Dictionnaire dico; std::string def;
dico.addWord("mer", "Grande baignoire avec des vagues");
std::thread t1(&Dictionnaire::addWord, &dico, "océan", "Comme la mer, mais en plus froid" );
std::thread t2(&Dictionnaire::getDefinition, &dico, "mer", std::ref(def) );
std::thread t3(&Dictionnaire::addWord, &dico, "vent", "Substance que certains aiment brasser."   );
std::thread t4(&Dictionnaire::addWord, &dico, "alea jacta est", "Ils sont bavards à la gare de l'Est."   );
t1.join(); t2.join(); t3.join(); t4.join();

    std::cout << "Definition de mer : " << def << std::endl;
    std::cout << "Dans le dictionnaire : " << std::endl;
    for (auto const& val : dico)
        std::cout << "\t" << val.first << " : " << val.second << std::endl; 
    return EXIT_SUCCESS;
}
