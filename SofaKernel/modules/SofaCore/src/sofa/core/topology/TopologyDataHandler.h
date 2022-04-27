/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#pragma once
#include <sofa/core/config.h>

#include <sofa/core/topology/TopologyHandler.h>
#include <sofa/core/topology/BaseTopologyData.h>

#include <sofa/core/topology/BaseTopology.h>


namespace sofa::core::topology
{



////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////   Generic Topology Data Implementation   /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class TopologyElementType, class VecT>
class TopologyDataHandler : public sofa::core::topology::TopologyHandler
{
public:
    typedef VecT container_type;
    typedef typename container_type::value_type value_type;
    typedef sofa::core::topology::BaseTopologyData<VecT> t_topologicalData;

    typedef core::topology::TopologyElementInfo<TopologyElementType> ElementInfo;
    typedef core::topology::TopologyChangeElementInfo<TopologyElementType> ChangeElementInfo;

    typedef core::topology::BaseMeshTopology::Point Point;
    typedef core::topology::BaseMeshTopology::Edge Edge;
    typedef core::topology::BaseMeshTopology::Triangle Triangle;
    typedef core::topology::BaseMeshTopology::Quad Quad;
    typedef core::topology::BaseMeshTopology::Tetrahedron Tetrahedron;
    typedef core::topology::BaseMeshTopology::Hexahedron Hexahedron;

    // Event types (EMoved* are not used for all element types, i.e. Point vs others)
    typedef typename ChangeElementInfo::EIndicesSwap    EIndicesSwap;
    typedef typename ChangeElementInfo::ERenumbering    ERenumbering;
    typedef typename ChangeElementInfo::EAdded          EAdded;
    typedef typename ChangeElementInfo::ERemoved        ERemoved;
    typedef typename ChangeElementInfo::EMoved          EMoved;
    typedef typename ChangeElementInfo::EMoved_Removing EMoved_Removing;
    typedef typename ChangeElementInfo::EMoved_Adding   EMoved_Adding;
    typedef typename ChangeElementInfo::AncestorElem    AncestorElem;

    TopologyDataHandler(t_topologicalData* _topologicalData,
        sofa::core::topology::BaseMeshTopology* _topology, 
        value_type defaultValue = value_type());


    TopologyDataHandler(t_topologicalData* _topologicalData,
        value_type defaultValue = value_type());

    void init();

    void handleTopologyChange() override;

    void registerTopologicalData(t_topologicalData *topologicalData) {m_topologyData = topologicalData;}


    /// Function to link DataEngine with Data array from topology
    void linkToPointDataArray() override;
    void linkToEdgeDataArray() override;
    void linkToTriangleDataArray() override;
    void linkToQuadDataArray() override;
    void linkToTetrahedronDataArray() override;
    void linkToHexahedronDataArray() override;

    bool isTopologyDataRegistered() override;

    using TopologyHandler::ApplyTopologyChange;

    /// Apply swap between indices elements.
    virtual void ApplyTopologyChange(const EIndicesSwap* event) override;
    /// Apply adding elements.
    virtual void ApplyTopologyChange(const EAdded* event) override;
    /// Apply removing elements.
    virtual void ApplyTopologyChange(const ERemoved* event) override;
    /// Apply renumbering on elements.
    virtual void ApplyTopologyChange(const ERenumbering* event) override;
    /// Apply moving elements.
    virtual void ApplyTopologyChange(const EMoved* event) override;
    /// Apply adding function on moved elements.
    //virtual void ApplyTopologyChange(const EMoved_Adding* event) override;
    ///// Apply removing function on moved elements.
    //virtual void ApplyTopologyChange(const EMoved_Removing* event) override;



    ////////////////////////////////////// DEPRECATED ///////////////////////////////////////////

    SOFA_ATTRIBUTE_DISABLED("v22.06 (PR#)", "v22.06 (PR#)", "This method to remove current elements has been removed, Destroy/Create function have been replaced by TopologyChangeCallback.")
    virtual void applyDestroyFunction(Index, value_type&) = delete;

    SOFA_ATTRIBUTE_DISABLED("v22.06 (PR#)", "v22.06 (PR#)", "This method to add elements has been removed, Destroy/Create function have been replaced by TopologyChangeCallback.")
    virtual void applyCreateFunction(Index, value_type& t,
        const sofa::type::vector< Index >&,
        const sofa::type::vector< SReal >&) = delete;

    SOFA_ATTRIBUTE_DISABLED("v22.06 (PR#)", "v22.06 (PR#)", "This method to add elements has been removed, Destroy/Create function have been replaced by TopologyChangeCallback.")
    virtual void applyCreateFunction(Index i, value_type& t, const TopologyElementType&,
        const sofa::type::vector< Index >& ancestors,
        const sofa::type::vector< SReal >& coefs) = delete;

    SOFA_ATTRIBUTE_DISABLED("v22.06 (PR#)", "v22.06 (PR#)", "This method to add elements has been removed, Destroy/Create function have been replaced by TopologyChangeCallback.")
    virtual void applyCreateFunction(Index i, value_type& t, const TopologyElementType& e,
        const sofa::type::vector< Index >& ancestors,
        const sofa::type::vector< SReal >& coefs,
        const AncestorElem* /*ancestorElem*/) = delete;

    SOFA_ATTRIBUTE_DISABLED("v22.06 (PR#)", "v22.06 (PR#)", "This method has been removed as it has never been used and is not needed. Use TopologyChangeCallback to add a callback.")
    void setDefaultValue(const value_type& v) = delete;
    
    SOFA_ATTRIBUTE_DISABLED("v21.06 (PR#2171)", "v21.06 (PR#2171)", "This method has been removed as it has never been used and is not needed. Use TopologyChangeCallback to add a callback.")
    bool applyTestCreateFunction(Index /*index*/, const sofa::type::vector< Index >& /*ancestors*/, const sofa::type::vector< SReal >& /*coefs*/) = delete;

protected:
    t_topologicalData* m_topologyData;

public:
    bool m_pointsLinked;
    bool m_edgesLinked;
    bool m_trianglesLinked;
    bool m_quadsLinked;
    bool m_tetrahedraLinked;
    bool m_hexahedraLinked;

};


} //namespace sofa::core::topology
