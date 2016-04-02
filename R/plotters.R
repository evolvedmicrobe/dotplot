
#' Create dotplot using base graphics package
#'
#' @param seq1 String of first sequence
#' @param seq2 String of second sequence
#' @param wsize Window size
#' @param wstep Step size for windows (likely should be 1)
#' @param nmatch (Number of matches in window needed for plotting, defaults to wsize if negative)
#' @param ... Additional parameters for plot (xlab, ylab, main, etc.)
#'
#' @return Prints the plot
#' @export
dotPlotm <- function(seq1, seq2, wsize = 10, wstep = 1, nmatch = -1, ...)
{
  if (length(seq1[1]) > 1)
    stop("seq1 should be provided as a single string")
  if (length(seq2[1]) > 1)
    stop("seq2 should be provided as a single string")
  if (wsize < 1)
    stop("non allowed value for wsize")
  if (wstep < 1)
    stop("non allowed value for wstep")
  if (nmatch < 1)
    nmatch = wsize
  if (nmatch > wsize)
    stop("nmatch > wsize is not allowed")

  xy <- mkDotPlotMatrix(seq1, seq2, wsize, wstep, nmatch)
  xy = apply(xy, 2, rev)
  # Use raster grapics, see https://journal.r-project.org/archive/2011-1/RJournal_2011-1_Murrell.pdf
  x = seq(from = 1, to = (nchar(seq1) - wsize), length=50)
  y = seq(from = 1, to = (nchar(seq2) - wsize), length=50)
  xrange <- range(x) #+ c(-step/2, step/2)
  yrange <- range(y) #+ c(-step/2, step/2)
  plot(x, y, xlim=xrange, ylim=yrange, type="n", ...)
       #xaxs="i", yaxs="i", type="n") #"i" marks it as going right up to the edge
  rasterImage(xy, xrange[1], yrange[1],
              xrange[2], yrange[2],interpolate=FALSE)


}

#' Create dotplot using ggplot, X,Y points with a match will be
#'
#' @param seq1 String of first sequence
#' @param seq2 String of second sequence
#' @param wsize Window size
#' @param wstep Step size for windows (likely should be 1)
#' @param nmatch (Number of matches in window needed for plotting, defaults to wsize if negative)
#' @return
#' @export
#' @useDynLib dotplot
dotPlotg <- function (seq1, seq2, wsize = 10, wstep = 1, nmatch = -1)
{
  if (length(seq1[1]) > 1)
    stop("seq1 should be provided as a single string")
  if (length(seq2[1]) > 1)
    stop("seq2 should be provided as a single string")
  if (wsize < 1)
    stop("non allowed value for wsize")
  if (wstep < 1)
    stop("non allowed value for wstep")
  if (nmatch < 1)
    nmatch = wsize
  if (nmatch > wsize)
    stop("nmatch > wsize is not allowed")
  xy <- mkDotPlotDataFrame(seq1, seq2, wsize, wstep, nmatch)
  ggplot2::ggplot(xy, ggplot2::aes(x=x, y=y)) + ggplot2::geom_point(shape=15)
}
