/******************************************************************************
* Copyright (c) 2011, Howard Butler, hobu.inc@gmail.com
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#ifndef INCLUDED_PDAL_DRIVER_OCI_READER_HPP
#define INCLUDED_PDAL_DRIVER_OCI_READER_HPP

#include <pdal/pdal.hpp>

#include <pdal/Reader.hpp>
#include <pdal/drivers/oci/common.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#include <vector>

namespace pdal { namespace drivers { namespace oci {



class PDAL_DLL Reader : public pdal::Reader
{
public:
    SET_STAGE_NAME("drivers.oci.reader", "OCI Reader")

    Reader(const Options&);
    ~Reader();

    virtual void initialize();
    virtual const Options getDefaultOptions() const;
 
    bool supportsIterator (StageIteratorType t) const
    {   
        if (t == StageIterator_Sequential ) return true;
        return false;
    }

    boost::uint64_t getNumPoints() { return 0; }
    
    pdal::StageSequentialIterator* createSequentialIterator() const;
    
    Connection getConnection () const { return m_connection;}
    Statement getStatement () const { return m_statement;}
    CloudPtr getCloud() const;
    std::string getQuery() const;

    // for dumping
    virtual boost::property_tree::ptree toPTree() const;

private:

    Reader& operator=(const Reader&); // not implemented
    Reader(const Reader&); // not implemented
    // 
    
    QueryType describeQueryType() const;
    Schema fetchSchema(sdo_pc* pc);

    Connection m_connection;
    Statement m_statement;
    QueryType m_querytype;

    sdo_pc* m_pc;
    sdo_pc_blk* m_pc_block;
    boost::uint32_t m_capacity;

};

}}} // namespace pdal::driver::oci


#endif // INCLUDED_PDAL_DRIVER_OCI_READER_HPP
