#ifndef PROPERTYNULL_HPP_INCLUDED
#define PROPERTYNULL_HPP_INCLUDED


/* mire jó: getter és setter helyettesítése egy publikus, fiktív adattaggal. */

#define PROPERTYNULL(parent, return_type, name) PropertyNull<parent, return_type, (& parent :: set##name), (& parent :: get##name), (& parent :: set##name)> name{*this}

/* property: milyen CLASS-hoz, milyen T típusú adattag,
 * melyik SETTERPTR tagfüggvény a setter, melyik GETTERPTR tagfüggvény a getter */
template <typename CLASS, typename T,
         void (CLASS::*SETTERPTR) (T const& newvalue),
         T (CLASS::*GETTERPTR) () const,
         void (CLASS::*SETTERPTRNULL) (std::nullptr_t newvalue)>
class PropertyNull
{
    CLASS& obj;
    /* copy ctor letiltása, hogy muszáj legyen megadni az új szülő
     * objektumot (különben másolódna a referencia!) */
    PropertyNull (PropertyNull const&) = delete;

public:
    /* a property szülő objektuma. ezt azért kell paraméterként átvenni,
     * mert c++ban nem lehet sehogy kitalálni egy objektumról, hogy egy
     * másik objektum része-e (subobject) */
    PropertyNull (CLASS& obj) : obj (obj) {}

    /* property beállítása */
    PropertyNull& operator= (T const& newvalue)
    {
        (obj.*SETTERPTR) (newvalue);
        return *this;
    }

    PropertyNull& operator= (std::nullptr_t newvalue)
    {
        (obj.*SETTERPTRNULL) (newvalue);
        return *this;
    }

    /* property lekérdezése */
    operator T () const
    {
        return (obj.*GETTERPTR) ();
    }

    /* property = property eset kezelése */
    PropertyNull& operator= (PropertyNull const& the_other)
    {
        *this = the_other.operator T&();
        return *this;
    }
};


#endif // PROPERTYNULL_HPP_INCLUDED
