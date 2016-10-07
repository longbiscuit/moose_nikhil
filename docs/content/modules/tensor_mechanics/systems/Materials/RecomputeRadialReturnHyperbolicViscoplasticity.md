#RecomputeRadialReturnHyperbolicViscoplasticity
!description /Materials/RecomputeRadialReturnHyperbolicViscoplasticity

!devel /Materials/RecomputeRadialReturnHyperbolicViscoplasticity float=right width=auto margin=20px padding=20px background-color=#F8F8F8

## Description
{!content/modules/tensor_mechanics/common_documentation/supplementalRecomputeRadialReturn.md!}

This uniaxial viscoplasticity class computes the plastic strain as a stateful material property.  The constitutive equation for scalar plastic strain rate used in this model is
$$
\dot{p} = \phi (\sigma_e , r) = \alpha sinh \beta (\sigma_e -r - \sigma_y)
$$

This class is based on the implicit integration algorithm in \cite{dunne2005introduction} pg. 162 - 163.

!parameters /Materials/RecomputeRadialReturnHyperbolicViscoplasticity

!inputfiles /Materials/RecomputeRadialReturnHyperbolicViscoplasticity

!childobjects /Materials/RecomputeRadialReturnHyperbolicViscoplasticity

## References
\bibliographystyle{unsrt}
\bibliography{docs/bib/tensor_mechanics.bib}