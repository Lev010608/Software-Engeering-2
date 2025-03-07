<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Fitness Center</TITLE>
            </HEAD>
            <BODY>
                Member's Names:
                <xsl:variable name="names" select="/FitnessCenter/Member[1]/Name"/>
                <xsl:for-each select="/FitnessCenter/Member[position() &gt; 1]">
                    <xsl:variable name="names" select="concat($names, '/')"/>
                    <xsl:variable name="names" select="concat($names, Name)"/>
                </xsl:for-each>
                <xsl:value-of select="$names"/>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>