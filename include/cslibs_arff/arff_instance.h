#ifndef __INCLUDED_ARFF_INSTANCE_H__
#define __INCLUDED_ARFF_INSTANCE_H__
/**
 * @file arff_instance.h
 * @brief Contains the 'ArffInstance' class
 */

#include <vector>
#include <memory>

#include "arff_utils.h"
#include "arff_value.h"


/**
 * @class ArffInstance arff_instance.h
 * @brief Class to represent one single instance of data
 */
class ArffInstance {
public:
    typedef std::shared_ptr<ArffInstance> Ptr;

    /**
     * @brief Constructor
     */
    ArffInstance();

    /**
     * @brief Destructor
     */
    virtual ~ArffInstance();

    /**
     * @brief Number of elements in the instance
     * @return number
     */
    std::size_t size()const;

    /**
     * @brief Add an instance data into the list
     * @param val the data to be added
     *
     * Note that this pointer will be owned by this class from here onwards!
     */
    void add(const ArffValue::Ptr &val);

    /**
     * @brief Get an instance data at the given location
     * @param idx location (starts from 0)
     * @return data
     *
     * Note that this pointer will still be owned by this class!
     */
    ArffValue::Ptr get(const std::size_t idx) const;


private:
    /** instance data */
    std::vector<ArffValue::Ptr> m_data;
}; 


/* DO NOT WRITE ANYTHING BELOW THIS LINE!!! */
#endif // __INCLUDED_ARFF_INSTANCE_H__
