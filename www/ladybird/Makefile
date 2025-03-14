PORTNAME=	ladybird
PORTVERSION=	g20240505
PORTREVISION=	2
CATEGORIES=	www
MASTER_SITES=	https://github.com/unicode-org/cldr-json/releases/download/${CLDRVERSION}/:cldr \
		https://www.unicode.org/Public/${UCDVERSION}/ucd/:ucd \
		https://www.unicode.org/Public/emoji/${UCDVERSION:R}/:emoji \
		https://www.unicode.org/Public/idna/${UCDVERSION}/:idna \
		https://curl.se/ca/:cacert
DISTFILES=	cldr-${CLDRVERSION}-json-modern.zip:cldr \
		UCD.zip:ucd \
		emoji-test.txt:emoji \
		IdnaMappingTable.txt:idna \
		cacert-${CACERTVERSION}.pem:cacert
DIST_SUBDIR=	${PORTNAME}-${PORTVERSION}
EXTRACT_ONLY=	${_DISTFILES:M*${GH_ACCOUNT}*}

PATCH_SITES=	https://github.com/LadybirdBrowser/ladybird/commit/
PATCHFILES=	397774d42272fff8dbc6d8d53616d79667d6608a.diff:-p1

MAINTAINER=	fuz@FreeBSD.org
COMMENT=	SerenityOS web browser
WWW=		https://ladybird.dev/

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

# see Userland/Libraries/LibWeb/Loader/ResourceLoader.h
ONLY_FOR_ARCHS=	aarch64 amd64 i386 riscv64
ONLY_FOR_ARCHS_REASON=	other architectures not recognised by build system

BUILD_DEPENDS=	${LOCALBASE}/share/public_suffix_list/public_suffix_list.dat:dns/public_suffix_list \
		${LOCALBASE}/share/color/Adobe/CMYK/USWebCoatedSWOP.icc:graphics/icc-profiles-adobe-cs4
RUN_DEPENDS=	${LOCALBASE}/share/fonts/Liberation/LiberationMono-Bold.ttf:x11-fonts/liberation-fonts-ttf

USES=		cmake:testing compiler:c++20-lang gl localbase:ldflags python:build qt:6
USE_GITHUB=	yes
GH_ACCOUNT=	SerenityOS
GH_PROJECT=	serenity
GH_TAGNAME=	3a7bea7402e879f731c9f4802cec84921f496942
USE_GL=		egl
USE_LDCONFIG=	yes
USE_QT=		base tools:build wayland multimedia

CACERTVERSION=	2023-08-22
CLDRVERSION=	44.0.1
UCDVERSION=	15.1.0

CMAKE_ARGS=	SERENITY_CACHE_DIR=${_DISTDIR}
CMAKE_OFF=	ENABLE_LAGOM_CCACHE \
		ENABLE_COMMONMARK_SPEC_DOWNLOAD \
		ENABLE_CACERT_DOWNLOAD \
		ENABLE_TIME_ZONE_DATABASE_DOWNLOAD \
		INCLUDE_WASM_SPEC_TESTS \
		INCLUDE_FLAC_SPEC_TESTS \
		ENABLE_NETWORK_DOWNLOADS
CMAKE_SOURCE_PATH=	${WRKSRC}/Ladybird

BINARY_ALIAS=	python3=${PYTHON_CMD}
DESKTOP_ENTRIES=	"Ladybird" "SerenityOS web browser" "ladybird" "${PREFIX}/bin/Ladybird" "Network;WebBrowser;" false

PLIST_FILES=	${PLIST_FILES_${ARCH}}
PLIST_FILES_amd64=	lib/liblagom-x86.so \
			lib/liblagom-x86.so.0 \
			lib/liblagom-x86.so.0.0.0

OPTIONS_DEFINE=	PULSEAUDIO
OPTIONS_DEFAULT=	PULSEAUDIO
PULSEAUDIO_LIB_DEPENDS=	libpulse.so:audio/pulseaudio
PULSEAUDIO_CMAKE_BOOL=	HAVE_PULSEAUDIO

post-extract:
	${MKDIR} ${CONFIGURE_WRKSRC}/caches/PublicSuffix ${CONFIGURE_WRKSRC}/caches/AdobeICCProfiles
	${LN} -s ${LOCALBASE}/share/public_suffix_list/public_suffix_list.dat \
	    ${CONFIGURE_WRKSRC}/caches/PublicSuffix/
	${LN} -s ${LOCALBASE}/share/color/Adobe ${CONFIGURE_WRKSRC}/caches/AdobeICCProfiles/'Adobe ICC Profiles (end-user)'

post-configure:
	${MKDIR} ${CONFIGURE_WRKSRC}/caches/CLDR ${CONFIGURE_WRKSRC}/caches/UCD
	${TAR} -x -C ${CONFIGURE_WRKSRC}/caches/CLDR -f ${_DISTDIR}/cldr-${CLDRVERSION}-json-modern.zip
	${TAR} -x -C ${CONFIGURE_WRKSRC}/caches/UCD -f ${_DISTDIR}/UCD.zip
	${CP} ${_DISTDIR}/emoji-test.txt ${CONFIGURE_WRKSRC}/caches/UCD
	${CP} ${_DISTDIR}/IdnaMappingTable.txt ${CONFIGURE_WRKSRC}/caches/UCD
	${CP} ${_DISTDIR}/cacert-${CACERTVERSION}.pem ${CONFIGURE_WRKSRC}/Lagom/cacert.pem

post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/share/icons/hicolor/256x256/apps
	${INSTALL_DATA} ${WRKSRC}/Ladybird/Icons/ladybird.png \
	    ${STAGEDIR}${PREFIX}/share/icons/hicolor/256x256/apps/

.include <bsd.port.mk>
