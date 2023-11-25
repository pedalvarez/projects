<template>
  <div>
    <div v-if="loading" class="centered">
      <i class="fa fa-spinner fa-pulse fa-pulse fa-3x fa-fw"></i>
    </div>
    <filter-bar
      v-on:filter-set="onFilterSet"
    ></filter-bar>
    <vuetable ref="vuetable"
              api-url="req"
              data-path="content"
              detail-row-id="id"
              :per-page=20
              detail-row-component="detail-row"
              v-on:vuetable:loading="onLoading"
              v-on:vuetable:loaded="onLoaded"
              v-on:vuetable:load-error="onLoadError"
              :css="css"
              :fields="fields"
              :query-params="{ sort: 'sort', page: 'page', perPage: 'pageSize'}"
              :append-params="filterParams"
              :sort-order="sortOrder"
              @vuetable:pagination-data="onPaginationData"
              @vuetable:cell-clicked="expandRow"
    ></vuetable>
    <vuetable-pagination-info ref="paginationInfo"
                              info-class="pull-left"
    ></vuetable-pagination-info>
    <vuetable-pagination ref="pagination"
                         :css="cssPagination"
                         :icons="icons"
                         @vuetable-pagination:change-page="onChangePage">
    </vuetable-pagination>
  </div>
</template>

<script>
  import Vue from 'vue'
  import VueEvents from 'vue-events'
  import {EventBus} from 'eventbus'
  import he from 'he'

  import Vuetable from 'vuetable-2/src/components/Vuetable'
  import VuetablePagination from 'vuetable-2/src/components/VuetablePagination'
  import VuetablePaginationInfo from 'vuetable-2/src/components/VuetablePaginationInfo'
  import FilterBar from 'components/FilterBar'
  import DetailRow from 'components/DetailRow'

  Vue.use(VueEvents)
  Vue.component('detail-row', DetailRow)

  import moment from 'moment'

  export default {
    components: {
      Vuetable,
      VuetablePagination,
      VuetablePaginationInfo,
      FilterBar
    },

    data () {
      return {
        css: {
          tableClass: 'ui blue selectable celled stackable attached table',
          loadingClass: 'loading',
          detailRowClass: 'vuetable-detail-row',
          sortHandleIcon: 'glyphicon glyphicon-sort',
          ascendingIcon: 'glyphicon glyphicon-arrow-up',
          descendingIcon: 'glyphicon glyphicon-arrow-down'
        },
        cssPagination: {
          wrapperClass: 'pagination pull-right',
          activeClass: 'btn-primary',
          disabledClass: 'disabled',
          pageClass: 'btn btn-border',
          linkClass: 'btn btn-border'
        },
        icons: {
          first: '',
          prev: '',
          next: '',
          last: ''
        },
        fields: [
          {
            name: 'id',
            sortField: 'id',
            titleClass: 'text-left',
            dataClass: 'text-left',
            callback: 'formatIdField'
          },
          {
            name: 'source',
            sortField: 'source',
            titleClass: 'text-left',
            dataClass: 'text-left',
            callback: 'formatIdField'
          },
          {
            name: 'shortText',
            sortField: 'shorttext',
            titleClass: 'text-left',
            dataClass: 'text-left',
            callback: 'escapeTags'
          },
          {
            name: 'status',
            sortField: 'status',
            titleClass: 'text-left',
            dataClass: 'text-left'
          },
          {
            name: 'given',
            sortField: 'given',
            titleClass: 'text-left',
            dataClass: 'text-left',
            callback: 'escapeTags'
          },
          {
            name: 'when',
            sortField: 'when',
            titleClass: 'text-left',
            dataClass: 'text-left',
            callback: 'escapeTags'
          },
          {
            name: 'then',
            sortField: 'then',
            titleClass: 'text-left',
            dataClass: 'text-left'
          }
        ],
        sortOrder: [
          {field: 'id', sortField: 'id', direction: 'desc', separator: ','}
        ],
        filterParams: {},
        loading: false
      }
    },

    methods: {
      getSortParam: function (sortOrder) {
        return sortOrder.map(function (sort) {
          return sort.field + ',' + (sort.direction === 'desc' ? 'desc' : 'asc')
        }).join(',')
      },
      formatIdField: function (value) {
        return `<i class='glyphicon glyphicon-chevron-right expandable'></i>${value}`
      },
      formatCreatedDateField: function (value) {
        return moment(value).format('YYYY-MM-DD HH:mm:ss.SSS')
      },
      escapeTags: function (value) {
        return he.escape(value)
      },
      transform: function (data) {
        let from = data.page.number * data.page.size + 1
        let transformed = {}
        transformed.links = {}
        transformed.links.pagination = {
          total: data.page.totalElements,
          per_page: data.content.length,
          current_page: data.page.number,
          last_page: data.page.totalPages,
          next_page_url: data.nextPage,
          prev_page_url: data.prevPage,
          from: from,
          to: from + data.content.length - 1
        }

        transformed.content = data.content
        return transformed
      },

      onPaginationData (paginationData) {
        this.$refs.pagination.setPaginationData(paginationData)
        this.$refs.paginationInfo.setPaginationData(paginationData)
      },
      onChangePage (page) {
        this.$refs.vuetable.changePage(page)
      },
      onFilterSet (filterParams) {
        console.log('filter set')
        this.filterParams = filterParams
        Vue.nextTick(() => this.$refs.vuetable.refresh())
        this.$refs.vuetable.tableData = []
      },
      onLoading () {
        console.log('loading')
        this.loading = true
      },
      onLoaded () {
        console.log('loaded')
        this.loading = false
      },
      onLoadError (error) {
        console.log('error')
        this.loading = false
        if (error.status === 403) {
          this.$router.push('/error')
        } else {
          EventBus.$emit('toast-error', 'Error loading requete entries', error)
        }
      },
      expandRow (data, field, event) {
        this.$refs.vuetable.toggleDetailRow(data.id)
      }
    }
  }
</script>

<style>
  i.expandable:hover {
    color: #2185d0;
    cursor: pointer;
  }
</style>
