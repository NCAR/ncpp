Summary: Spec file for ncpp
Name: ncpp
Version: 2.3
Release: 0%{?dist}
License: GPL
Group: System Environment/Daemons
Url: http://www.eol.ucar.edu/
Packager: Chris Webster <cjw@ucar.edu>
# becomes RPM_BUILD_ROOT
BuildRoot:  %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Vendor: UCAR
BuildArch: x86_64

Requires: netcdf-cxx netcdf libpng

%if 0%{?rhel} <= 7
BuildRequires: scons
Requires: openmotif 
%else
BuildRequires: python3-scons
Requires: motif
%endif

Source: ftp://ftp.eol.ucar.edu/pub/archive/RAF-src/%{name}.tar.gz

%description
Configuration for NCAR-EOL ncpp display for size-distribution data.

%prep
%setup -n %{name}

%build
scons 

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{_bindir}
cp src/%{name} %{buildroot}%{_bindir}

%post


%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root)
%{_bindir}/%{name}

%changelog
* Mon May 2 2022 Chris Webster <cjw@ucar.edu> - 2.3-0
- Add support for netCDF files with legacy size-distribution zero bin removed.
* Sat Mar 13 2021 Chris Webster <cjw@ucar.edu> - 2.2-6
- Maintenance for Macports builds
* Sat Mar 13 2021 Chris Webster <cjw@ucar.edu> - 2.2-5
- Refactor help menu to open URLs into default browser.
* Wed Jul 13 2011 Chris Webster <cjw@ucar.edu> - 1.0-1
- initial version
